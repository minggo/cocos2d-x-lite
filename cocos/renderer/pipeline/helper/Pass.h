#pragma once
#include "../Define.h"

namespace cc {
namespace pipeline {

struct CC_DLL Pass {
    uint phase;
    uint priority = (uint)RenderPriority::DEFAULT;
};

} // namespace pipeline
} // namespace cc
