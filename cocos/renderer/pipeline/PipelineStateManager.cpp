#include "PipelineStateManager.h"
#include "Define.h"
#include "gfx/GFXRenderPass.h"
#include "gfx/GFXInputAssembler.h"
#include "gfx/GFXDevice.h"
#include "helper/SubModel.h"
#include "helper/Pool.h"

namespace cc {
namespace pipeline {
map<uint, gfx::PipelineState *> PipelineStateManager::_PSOHashMap;
gfx::PipelineState* PipelineStateManager::getOrCreatePipelineStage(gfx::Device *device,
                                                                   const PSOInfo *PSOInfo,
                                                                   gfx::RenderPass *renderPass,
                                                                   gfx::InputAssembler *inputAssembler) {
    const auto psoInfoHash = PSOInfo->hash;
    const auto renderPassHash = renderPass->getHash();
    const auto attributesHash = inputAssembler->getAttributesHash();
    const auto hash = psoInfoHash ^ renderPassHash ^ attributesHash;

    auto *pso = _PSOHashMap[hash];
    if (!pso) {
        gfx::PipelineStateInfo info = {
            (gfx::PrimitiveMode)PSOInfo->primitive,
            ShaderPool::getShader(PSOInfo->shaderIndex),
            { inputAssembler->getAttributes() },
            PSOInfo->rs,//RasterizerStatePool::getRasterizerState(PSOInfo->rasterizerState)//PSOInfo.rasterizerState,
            PSOInfo->ds,
            PSOInfo->bs,
            DynamicStatePool::getDynamicStates(PSOInfo->dynamicStatesIndex, PSOInfo->dynamicStatesCount),
            renderPass
        };
        pso = device->createPipelineState(std::move(info));
        _PSOHashMap[hash] = pso;
    }

    return pso;
}

} // namespace pipeline
} // namespace cc
