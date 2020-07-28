#pragma once
#include "../Define.h"

namespace cc {
namespace pipeline {

struct CC_DLL Pass {
public:
    uint phase;
    RenderPriority priority = RenderPriority::DEFAULT;
};

} // namespace pipeline
} // namespace cc
