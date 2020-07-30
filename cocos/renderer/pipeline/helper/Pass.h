#pragma once
#include "../Define.h"

namespace cc {
namespace pipeline {

enum class BatchingSchemes :uint8_t {
    INSTANCING = 1,
    VB_MERGING = 2,
};

struct CC_DLL Pass {
    uint phase;
    uint priority = (uint)RenderPriority::DEFAULT;
    uint batchingScheme = 0;
};

} // namespace pipeline
} // namespace cc
