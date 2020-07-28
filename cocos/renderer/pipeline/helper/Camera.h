#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct CC_DLL Camera {
    bool isWindowSize = true;
    float screenScale = 0;
    uint clearStencil= 0;
    float clearDepth = 1.0f;
    gfx::ClearFlags clearFlag = gfx::ClearFlags::NONE;
    gfx::Rect viewport = {0, 0, 1, 1};
    float width = 0;
    float height = 0;
    gfx::Color clearColor = {0.2f, 0.2f, 0.2f, 1};

};

} //namesapce pipeline
} //namespace cc
