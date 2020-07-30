#include "RenderQueue.h"
#include "base/Log.h"
#include "gfx/GFXShader.h"
#include "gfx/GFXCommandBuffer.h"
#include "PipelineStateManager.h"
#include "helper/Model.h"
#include "helper/SubModel.h"
#include "helper/Pass.h"
#include "helper/Pool.h"

namespace cc {
namespace pipeline {

RenderQueue::RenderQueue(const RenderQueueDesc &desc) {
    _passDesc = desc;
    _queue.resize(64);
}

void RenderQueue::clear() {
    _queue.clear();
}

bool RenderQueue::insertRenderPass(const RenderObject &renderObj, uint subModelIdx, uint passIdx) {
    const auto *model = ModelPool::getModel(renderObj.modelIndex);
    auto *subModel = SubModelPool::getSubModel(model->subModelsIndex) + subModelIdx;
    const auto *pass = PassPool::getPass(subModel->passesIndex) + passIdx;
    const auto *psoInfo = PSOInfoPool::getPSOInfo(subModel->psoInfosIndex) + passIdx;
    const auto &blendTargets = BlendTargetPool::getBlendTarget(psoInfo->bs.targetIndex, psoInfo->bs.targetCount);
    const auto isTransparent = blendTargets[0].blend;

    if (isTransparent != _passDesc.isTransparent || !(pass->phase & _passDesc.phases)) {
        return false;
    }

    const auto hash = (0 << 30) | static_cast<uint>(pass->priority) << 16 | static_cast<uint>(subModel->priority) << 8 | passIdx;
    RenderPass renderPass;
    renderPass.hash = hash;
    renderPass.depth = renderObj.depth;
    renderPass.shaderID = ShaderPool::getShader(psoInfo->shaderIndex)->getHash();
    renderPass.index = passIdx;
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
        const auto passIdx = _queue[i].index;
        auto *ia = InputAssemblerPool::getInputAssembler(subModel->inputAssemblerIndex);
        const auto *psoInfo = PSOInfoPool::getPSOInfo(subModel->psoInfosIndex) + passIdx;
        auto *pso = PipelineStateManager::getOrCreatePipelineStage(device, psoInfo, renderPass, ia);
        cmdBuff->bindPipelineState(pso);
        cmdBuff->bindBindingLayout(BindingLayoutPool::getBindingLayout(psoInfo->bindingLayoutIndex));
        cmdBuff->bindInputAssembler(ia);
        cmdBuff->draw(ia);
    }
}
    
} // namespace pipeline
} // namespace cc
