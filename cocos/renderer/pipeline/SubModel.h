#pragma once

namespace cc {
namespace scene {

struct Pass;
struct RnederPriority;

struct CC_DLL PSOCreateInfo {
public:
    gfx::Shader* shader = nullptr;
    gfx::PrimitiveMode primitive = gfx::PrimitiveMode::TRIANGLE_LIST;
    gfx::RasterizerState rasterizerState;
    gfx::DepthStencilState depthStencilState;
    gfx::BlendState blendState;
    gfx::DynamicStateList dynamicStates;
    gfx::BindingLayout* bindingLayout;
    uint hash = 0;
};
typedef vector<PSOCreateInfo> PSOCreateInfoList;

struct CC_DLL SubModel {
public:
    vector<Pass *> passes;
    PSOCreateInfoList psoInfos;
    pipeline::RenderPriority priority = pipeline::RenderPriority::DEFAULT;
    gfx::InputAssembler *inputAssembler = nullptr;
};
typedef vector<SubModel *> SubModelList;

} //namespace renderer
} //namespace cc
