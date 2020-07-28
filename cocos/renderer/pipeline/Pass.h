#pragma once

namespace cc {
namespace scene {

namespace pipline {
struct RenderPriority;
}

struct CC_DLL Pass {
public:
    uint phase;
    pipeline::RenderPriority priority = pipeline::RenderPriority::DEFAULT;
};

} // namespace renderer
} // namespace cc
