#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {
struct SubModel;
struct PSOInfo;
struct Pass;
struct Model;

class CC_DLL PassPool {
public:
    static Pass* getPass(uint index);
};

class CC_DLL ModelPool {
public:
    static Model* getModel(uint index);
};

class CC_DLL SubModelPool {
public:
    static SubModel* getSubModel(uint index);
};

class CC_DLL PSOInfoPool {
public:
    static PSOInfo* getPSOInfo(uint index);
};

class CC_DLL BlendTargetPool {
public:
    static gfx::BlendTargetList getBlendTarget(uint index, uint count);
};

class CC_DLL ShaderPool {
public:
    static gfx::Shader* getShader(uint index);
};

class CC_DLL InputAssemblerPool {
public:
    static gfx::InputAssembler* getInputAssembler(uint index);
};

class CC_DLL DynamicStatePool {
public:
    static gfx::DynamicStateList getDynamicStates(uint index, uint count);
};

} //namespace pipeline
} //namespace cc
