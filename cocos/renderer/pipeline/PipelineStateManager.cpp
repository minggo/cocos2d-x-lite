#include "PipelineStateManager.h"
#include "Define.h"
#include "gfx/GFXRenderPass.h"
#include "gfx/GFXInputAssembler.h"
#include "gfx/GFXDevice.h"
#include "helper/SubModel.h"

namespace cc {
namespace pipeline {
map<uint, gfx::PipelineState *> PipelineStateManager::_PSOHashMap;
gfx::PipelineState* PipelineStateManager::getOrCreatePipelineStage(gfx::Device *device,
                                                                   const PSOCreateInfo &PSOInfo,
                                                                   gfx::RenderPass *renderPass,
                                                                   gfx::InputAssembler *inputAssembler) {
    const auto psoInfoHash = PSOInfo.hash;
    const auto renderPassHash = renderPass->getHash();
    const auto attributesHash = inputAssembler->getAttributesHash();
    const auto hash = psoInfoHash ^ renderPassHash ^ attributesHash;

    auto *pso = _PSOHashMap[hash];
    if (!pso) {
        gfx::PipelineStateInfo info = {
            PSOInfo.primitive,
            PSOInfo.shader,
            { inputAssembler->getAttributes() },
            PSOInfo.rasterizerState,
            PSOInfo.depthStencilState,
            PSOInfo.blendState,
            PSOInfo.dynamicStates,
            renderPass
        };
        pso = device->createPipelineState(std::move(info));
        _PSOHashMap[hash] = pso;
    }

    return pso;
}

} // namespace pipeline
} // namespace cc
