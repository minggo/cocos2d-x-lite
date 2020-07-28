#include "RenderStage.h"
#include "RenderFlow.h"
#include "RenderQueue.h"
#include "RenderPipeline.h"
#include "Model.h"
#include "SubModel.h"
#include "RenderView.h"
#include "Camera.h"
#include "RenderWindow.h"
#include "gfx/GFXFramebuffer.h"
#include "gfx/GFXCommandBuffer.h"

namespace cc {
namespace pipeline {

namespace {
size_t opaqueCompareFn(const RenderPass &a, const RenderPass &b) {
    return (a.hash - b.hash) || (a.depth - b.depth) || (a.shaderID - b.shaderID);
}

size_t transparentCompareFn(const RenderPass& a, const RenderPass& b) {
    return (a.hash - b.hash) || (b.depth - a.depth) || (a.shaderID - b.shaderID);
}
}

RenderStage::RenderStage() : GFXObject(gfx::ObjectType::RENDER_STAGE) {
}

bool RenderStage::initialize(const RenderStageInfo &info) {
    _name = info.name;
    _priority = info.priority;
    _framebufferName = info.framebuffer;
    _renderQueueDescriptors = info.renderQueues;
    
    return true;
}

void RenderStage::activate(RenderFlow *flow) {
    _flow = flow;
    _pipeline = flow->getPipeline();
    
    //TODO coulsonwang
//    if (!PipelineGlobal.device) {
//        CC_LOG_ERROR("RenderStage::activate: device is nullptr.");
//    }
    gfx::Color color = {0.3f, 0.6f, 0.9f, 1.0f};
    _clearColors.emplace_back(std::move(color));
    
    for (const auto &renderQueueDescriptor : _renderQueueDescriptors) {
        uint phases = 0;
        for(const auto &stage : renderQueueDescriptor.stages ) {
            phases |= PassPhase::getPhaseID(stage);
        }
        
        std::function<size_t(const RenderPass&, const RenderPass&)> sortFunc = opaqueCompareFn;
        switch (renderQueueDescriptor.sortMode) {
            case RenderQueueSortMode::BACK_TO_FRONT:
                sortFunc = transparentCompareFn;
                break;
            case RenderQueueSortMode::FRONT_TO_BACK:
                sortFunc = opaqueCompareFn;
            default:
                break;
        }
        RenderPassDesc renderPassDescriptor = {renderQueueDescriptor.isTransparent, phases, sortFunc};
        _renderQueues.emplace_back(CC_NEW(RenderQueue(std::move(renderPassDescriptor))));
    }
    
    if(_framebufferName == "window") {
//        _framebuffer = PipelineGlobal.root.mainWindow!.framebuffer; //TODO coulsonwang
    } else {
        _framebuffer = _flow->getPipeline()->getFramebuffer(_framebufferName);
    }
}

void RenderStage::executeCommandBuffer(RenderView *view) {
    const auto *camera = view->getCamera();
    const auto &viewport = camera->viewport;
    _renderArea.x = viewport.x * camera->width;
    _renderArea.y = viewport.y * camera->height;
    _renderArea.width = viewport.width * camera->width * _pipeline->getShadingScale();
    _renderArea.height = viewport.height * camera->height * _pipeline->getShadingScale();
    
    if(camera->clearFlag & gfx::ClearFlagBit::COLOR) {
        _clearColors[0] = camera->clearColor;
    }
    
    if(!_framebuffer) {
        _framebuffer = view->getWindow()->getFramebuffer();
    }
    
    auto *renderPass = _framebuffer->getRenderPass();
    auto *cmdBuffer = _pipeline->getCommandBuffers()[0];
    cmdBuffer->begin();
    cmdBuffer->beginRenderPass(renderPass,
                             _framebuffer,
                             _renderArea,
                             _clearColors,
                             camera->clearDepth,
                             camera->clearStencil);

    for (auto *renderQueue : _renderQueues) {
//        renderQueue->recordCommandBuffer(PipelineGlobal.device, renderPass, cmdBuffer); //TODO coulsonwang
    }

    cmdBuffer->endRenderPass();
    cmdBuffer->end();

//    PipelineGlobal.device.queue.submit(this._pipeline.commandBuffers); //TODO coulsonwang
}

void RenderStage::setClearColor(const gfx::Color &color) {
    if(_clearColors.size() > 0) {
        _clearColors[0] = color;
    } else {
        _clearColors.emplace_back(color);
    }
}

void RenderStage::setClearColors(const gfx::ColorList &colors) {
    _clearColors = colors;
}

void RenderStage::setClearDepth(float depth) {
    _clearDepth = depth;
}

void RenderStage::setClearStencil(uint stencil) {
    _clearStencil = stencil;
}

void RenderStage::setRenderArea(size_t width, size_t height) {
    _renderArea.width = width;
    _renderArea.height = height;
}

void RenderStage::sortRenderQueue() {
    for(auto * renderQueue : _renderQueues) {
        renderQueue->clear();
    }
    
    const auto &renderObjects = _pipeline->getRenderObjects();
    for(const auto &renderObject : renderObjects) {
        for(size_t i = 0; i < renderObject.model->subModels.size(); i++) {
            for(size_t j = 0; j < renderObject.model->subModels[i]->passes.size(); j ++) {
                for (auto &renderQueue : _renderQueues) {
                    renderQueue->insertRenderPass(renderObject, i, j);
                }
            }
        }
    }
    
    for(auto * renderQueue : _renderQueues) {
        renderQueue->sort();
    }
}

} // namespace pipeline
} // namespace cc
