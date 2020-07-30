#pragma once
#include "core/CoreStd.h"
#include "math/Mat4.h"

namespace cc {
namespace pipeline {


struct CC_DLL InstancedAttribute {
    uint nameIndex = 0;
    uint format = 0;
    uint isNormalized = 0;
    uint viewIndex = 0;
};

struct CC_DLL InstancedAttributeBlock {
    uint bufferViewIndex = 0;
    uint bufferViewSize = 0;
    uint instancedAttributesIndex = 0;
    uint instancedAttributesCount = 0;
};

struct CC_DLL Model {
public:
    uint subModelsIndex = 0; //vector<SubModel *>
    uint subModelsCount = 0;
    uint isDynamicBatching = 0;
    InstancedAttributeBlock instancedAttributes;
    cc::Mat4 worldMatrix;
};

} //namespace pipeline
} //namespace cc
