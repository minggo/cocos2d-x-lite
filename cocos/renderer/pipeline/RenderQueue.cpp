#include "RenderQueue.h"
#include "base/Log.h"
#include "gfx/GFXShader.h"
#include "gfx/GFXCommandBuffer.h"
#include "PipelineStateManager.h"
#include "Model.h"
#include "SubModel.h"
#include "Pass.h"

namespace cc {
namespace pipeline {

RenderQueue::RenderQueue(const RenderPassDesc &desc):GFXObject(gfx::ObjectType::RENDER_QUEUE) {
    _passDesc = desc;
    _queue.resize(64);
}

void RenderQueue::clear() {
    _queue.clear();
}

bool RenderQueue::insertRenderPass(const RenderObject &renderObj, uint subModelIdx, uint passIdx) {
    const auto *subModel = renderObj.model->subModels[subModelIdx];
    const auto *pass = subModel->passes[passIdx];
    const auto &psoInfo = subModel->psoInfos[passIdx];
    const auto isTransparent = psoInfo.blendState.targets[0].blend;
    
    if (isTransparent != _passDesc.isTransparent || !(pass->phase & _passDesc.phases)) {
        return false;
    }
    
    const auto hash = (0 << 30) | static_cast<uint>(pass->priority) << 16 | static_cast<uint>(subModel->priority) << 8 | passIdx;
    RenderPass renderPass;
    renderPass.hash = hash;
    renderPass.depth = renderObj.depth;
    renderPass.shaderID = psoInfo.shader->getHash();
    renderPass.passIdx = passIdx;
    renderPass.subModel = subModel;

    _queue.emplace_back(std::move(renderPass));
    return true;
}

void RenderQueue::sort() {
    std::sort(_queue.begin(), _queue.end(), _passDesc.sortFunc);
}

void RenderQueue::recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuff) {
    for (size_t i = 0; i < _queue.size(); ++i) {
        const auto *subModel = _queue[i].subModel;
        const auto passIdx = _queue[i].passIdx;
        auto *ia = subModel->inputAssembler;
        const auto &psoInfo = subModel->psoInfos[passIdx];
        auto *pso = PipelineStateManager::getOrCreatePipelineStage(device, psoInfo, renderPass, ia);
        cmdBuff->bindPipelineState(pso);
        cmdBuff->bindBindingLayout(psoInfo.bindingLayout);
        cmdBuff->bindInputAssembler(ia);
        cmdBuff->draw(ia);
    }
}
    
} // namespace pipeline
} // namespace cc
