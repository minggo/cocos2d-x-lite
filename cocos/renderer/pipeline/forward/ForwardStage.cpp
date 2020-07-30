#include "ForwardStage.h"
#include "pipeline/RenderBatchedQueue.h"
#include "pipeline/RenderInstancedQueue.h"
#include "pipeline/RenderAdditiveLightQueue.h"
#include "pipeline/RenderQueue.h"
#include "pipeline/helper/SubModel.h"
#include "pipeline/RenderPipeline.h"
#include "pipeline/helper/Pool.h"
#include "pipeline/helper/Model.h"
#include "pipeline/helper/SubModel.h"
#include "pipeline/helper/Pass.h"
#include "pipeline/InstancedBuffer.h"
#include "pipeline/BatchedBuffer.h"

namespace cc {
namespace pipeline {

//const RenderStageInfo &ForwardStage::getInitializeInfo() {
//
//}

ForwardStage::ForwardStage() : RenderStage(){
    _batchedQueue = CC_NEW(RenderBatchedQueue);
    _instancedQueue = CC_NEW(RenderInstancedQueue);
    _additiveLightQueue = CC_NEW(RenderAdditiveLightQueue);
}

ForwardStage::~ForwardStage() {
    destroy();
}

void ForwardStage::activate(RenderFlow *flow) {
    RenderStage::activate(flow);
}

void ForwardStage::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    CC_SAFE_DELETE(_instancedQueue);
    CC_SAFE_DELETE(_additiveLightQueue);
    for(auto *renderQueue : _renderQueues) {
        CC_SAFE_DELETE(renderQueue);
    }
    _renderQueues.clear();
}

void ForwardStage::resize(uint width, uint height) {
}

void ForwardStage::rebuild() {
}

void ForwardStage::render(RenderView *view) {
    _instancedQueue->clear();
    _batchedQueue->clear();
    const auto &validLights = _pipeline->getValidLights();
    const auto &lightBuffers = _pipeline->getLightBuffers();
    const auto &lightIndices = _pipeline->getLightIndices();
    _additiveLightQueue->clear(validLights, lightBuffers, lightIndices);
    
    for(auto renderQueue : _renderQueues) {
        renderQueue->clear();
    }

    const auto &renderObjects = _pipeline->getRenderObjects();
    const auto &lightIndexOffset = _pipeline->getLightIndexOffsets();
    size_t m = 0, p = 0, k = 0;
    for (size_t i = 0; i < renderObjects.size(); ++i) {
        auto nextLightIndex = i + 1 < renderObjects.size() ? lightIndexOffset[i + 1] : lightIndices.size();
        const auto &ro = renderObjects[i];
        auto *model = GET_MODEL(ro.modelIndex);
        if (model->isDynamicBatching) {
            for (m = 0; m < model->subModelsCount; ++m) {
                auto* subModel = GET_SUBMODEL(model->subModelsIndex, m);
                for (p = 0; p < subModel->passesCount; ++p) {
                    auto *pass = GET_PASS(subModel->passesIndex, p);
                    if (pass->batchingScheme == (uint)BatchingSchemes::INSTANCING) {
                        auto *instancedBuffer = InstancedBuffer::get(pass);
                        instancedBuffer->merge(subModel, model->instancedAttributes, GET_PSOINFO(subModel->psoInfosIndex));
                        _instancedQueue->getQueue().insert(instancedBuffer);
                    } else if (pass->batchingScheme == (uint)BatchingSchemes::VB_MERGING) {
                        auto *batchedBuffer = BatchedBuffer::get(pass);
                        batchedBuffer->merge(subModel, p, ro);
                        _batchedQueue->getQueue().insert(batchedBuffer);
                    } else {
                        for (k = 0; k < _renderQueues.size(); k++) {
                            _renderQueues[k]->insertRenderPass(ro, m, p);
                        }
                        _additiveLightQueue->add(ro, m, pass, lightIndexOffset[i], nextLightIndex);
                    }
                }
            }
        } else {
//            for (m = 0; m < ro.model.subModelNum; m++) {
//                for (p = 0; p < ro.model.getSubModel(m).passes.length; p++) {
//                    const pass = ro.model.getSubModel(m).passes[p];
//                    for (k = 0; k < this._renderQueues.length; k++) {
//                        this._renderQueues[k].insertRenderPass(ro, m, p);
//                    }
//                    this._additiveLightQueue.add(ro, m, pass, lightIndexOffset[i], nextLightIndex);
//                }
//            }
        }
    }
//    this._renderQueues.forEach(this.renderQueueSortFunc);
//
//    const camera = view.camera;
//
//    const cmdBuff = this._pipeline.commandBuffers[0];
//
//    const vp = camera.viewport;
//    this._renderArea!.x = vp.x * camera.width;
//    this._renderArea!.y = vp.y * camera.height;
//    this._renderArea!.width = vp.width * camera.width * this.pipeline!.shadingScale;
//    this._renderArea!.height = vp.height * camera.height * this.pipeline!.shadingScale;
//
//    if (camera.clearFlag & GFXClearFlag.COLOR) {
//        if (this._pipeline.isHDR) {
//            SRGBToLinear(colors[0], camera.clearColor);
//            const scale = this._pipeline.fpScale / camera.exposure;
//            colors[0].r *= scale;
//            colors[0].g *= scale;
//            colors[0].b *= scale;
//        } else {
//            colors[0].r = camera.clearColor.r;
//            colors[0].g = camera.clearColor.g;
//            colors[0].b = camera.clearColor.b;
//        }
//    }
//
//    colors[0].a = camera.clearColor.a;
//
//    let framebuffer = view.window.framebuffer;
//    if (this._pipeline.usePostProcess) {
//        if (!this._pipeline.useMSAA) {
//            framebuffer = this._pipeline.getFrameBuffer(this._pipeline!.currShading)!;
//        } else {
//            framebuffer = this._pipeline.getFrameBuffer('msaa')!;
//        }
//    }
//
//    const device = PipelineGlobal.device;
//    const renderPass = framebuffer.colorTextures[0] ? framebuffer.renderPass : this._flow.getRenderPass(camera.clearFlag);
//
//    cmdBuff.begin();
//    cmdBuff.beginRenderPass(renderPass, framebuffer, this._renderArea!,
//        colors, camera.clearDepth, camera.clearStencil);
//
//    this._renderQueues[0].recordCommandBuffer(device, renderPass, cmdBuff);
//    this._instancedQueue.recordCommandBuffer(device, renderPass, cmdBuff);
//    this._batchedQueue.recordCommandBuffer(device, renderPass, cmdBuff);
//    this._additiveLightQueue.recordCommandBuffer(device, renderPass, cmdBuff);
//    camera.scene!.planarShadows.recordCommandBuffer(device, renderPass, cmdBuff);
//    this._renderQueues[1].recordCommandBuffer(device, renderPass, cmdBuff);
//
//    cmdBuff.endRenderPass();
//    cmdBuff.end();
//
//    device.queue.submit(this._pipeline.commandBuffers);
//
//    if (this._pipeline.useMSAA) {
//        device.blitFramebuffer(
//            this._framebuffer!,
//            this._pipeline.getFrameBuffer(this._pipeline.currShading)!,
//            this._renderArea!,
//            this._renderArea!,
//            GFXFilter.POINT);
//    }
}

} // namespace pipeline
} // namespace cc
