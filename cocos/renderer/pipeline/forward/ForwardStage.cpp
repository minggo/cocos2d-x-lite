#include "ForwardStage.h"
#include "../RenderBatchedQueue.h"
#include "../RenderInstancedQueue.h"
#include "../RenderAdditiveLightQueue.h"
#include "../RenderQueue.h"
#include "../SubModel.h"


namespace cc {
namespace pipeline {

//const RenderStageInfo &ForwardStage::getInitializeInfo() {
//
//}

ForwardStage::ForwardStage() : RenderStage(){
    _batchedQueue = CC_NEW(RenderBatchedQueue);
    _instancedQueue = CC_NEW(RenderInstancedQueue);
    _additiveLightQueue = CC_NEW(RenderAdditiveLightQueue);
    
    _status = gfx::Status::SUCCESS;
}

ForwardStage::~ForwardStage() {
    destroy();
    _status = gfx::Status::UNREADY;
}

void ForwardStage::activate(RenderFlow *flow) {
//    RenderStage::activate(flow);
}

void ForwardStage::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    CC_SAFE_DELETE(_instancedQueue);
    CC_SAFE_DELETE(_additiveLightQueue);
//    for(auto *renderQueue : _renderQueues) {
//        CC_SAFE_DELETE(renderQueue);
//    }
//    _renderQueues.clear();
}

void ForwardStage::resize(uint width, uint height) {
}

void ForwardStage::rebuild() {
}

void ForwardStage::render(RenderView *view) {
//    _instancedQueue->clear();
//    _batchedQueue->clear();
    
//    const validLights = _pipeline->getvalid
//    const lightBuffers = this.pipeline.lightBuffers;
//    const lightIndices = this.pipeline.lightIndices;
//    this._additiveLightQueue.clear(validLights, lightBuffers, lightIndices);
//    this._renderQueues.forEach(this.renderQueueClearFunc);
//
//    const renderObjects = this._pipeline.renderObjects;
//    const lightIndexOffset = this.pipeline.lightIndexOffsets;
//    let m = 0; let p = 0; let k = 0;
//    for (let i = 0; i < renderObjects.length; ++i) {
//        const nextLightIndex = i + 1 < renderObjects.length ? lightIndexOffset[i + 1] : lightIndices.length;
//        const ro = renderObjects[i];
//        if (ro.model.isDynamicBatching) {
//            const subModels = ro.model.subModels;
//            for (m = 0; m < subModels.length; ++m) {
//                const subModel = subModels[m];
//                const passes = subModel.passes;
//                for (p = 0; p < passes.length; ++p) {
//                    const pass = passes[p];
//                    if (pass.batchingScheme === BatchingSchemes.INSTANCING) {
//                        const instancedBuffer = InstancedBuffer.get(pass);
//                        instancedBuffer.merge(subModel, ro.model.instancedAttributes, subModel.psoInfos[p]);
//                        this._instancedQueue.queue.add(instancedBuffer);
//                    } else if (pass.batchingScheme === BatchingSchemes.VB_MERGING) {
//                        const batchedBuffer = BatchedBuffer.get(pass);
//                        batchedBuffer.merge(subModel, p, ro);
//                        this._batchedQueue.queue.add(batchedBuffer);
//                    } else {
//                        for (k = 0; k < this._renderQueues.length; k++) {
//                            this._renderQueues[k].insertRenderPass(ro, m, p);
//                        }
//                        this._additiveLightQueue.add(ro, m, pass, lightIndexOffset[i], nextLightIndex);
//                    }
//                }
//            }
//        } else {
//            for (m = 0; m < ro.model.subModelNum; m++) {
//                for (p = 0; p < ro.model.getSubModel(m).passes.length; p++) {
//                    const pass = ro.model.getSubModel(m).passes[p];
//                    for (k = 0; k < this._renderQueues.length; k++) {
//                        this._renderQueues[k].insertRenderPass(ro, m, p);
//                    }
//                    this._additiveLightQueue.add(ro, m, pass, lightIndexOffset[i], nextLightIndex);
//                }
//            }
//        }
//    }
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
