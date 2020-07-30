#pragma once
#include "../Define.h"

namespace cc {
namespace pipeline {

struct Pass;
struct RnederPriority;

struct CC_DLL PSOInfo {
    uint shaderIndex = 0;//gfx::Shader*
    uint primitive = (uint)gfx::PrimitiveMode::TRIANGLE_LIST; //gfx::PrimitiveMode
    gfx::RasterizerState rs;
    gfx::DepthStencilState ds;
    gfx::BlendState bs;
    uint dynamicStatesIndex = 0; //gfx::DynamicStateList
    uint dynamicStatesCount = 0;
    uint bindingLayoutIndex = 0; //gfx:::BindingLayout*
    uint hash = 0;
};

struct CC_DLL SubModel {
    uint passesIndex = 0; //vector<Pass *>
    uint passesCount = 0;
    uint psoInfosIndex = 0; //PSOCreateInfoList
    uint priority = (uint)RenderPriority::DEFAULT; //RenderPriority
    uint inputAssemblerIndex = 0; //gfx::InputAssembler *
    uint subMeshIndex = 0;
};

} //namespace pipeline
} //namespace cc
