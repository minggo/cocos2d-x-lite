#pragma once

#include "core/CoreStd.h"

namespace cc {

namespace gfx {
class Device;
class InputAssembler;
class PipelineState;
class RenderPass;
};

namespace scene {
    struct PSOCreateInfo;
}

namespace pipeline {

class CC_DLL PipelineStateManager {
public:
    static gfx::PipelineState *getOrCreatePipelineStage(gfx::Device *device,
                                                           const scene::PSOCreateInfo &PSOInfo,
                                                           gfx::RenderPass *renderPass,
                                                           gfx::InputAssembler *inputAssembler);
    
private:
    static map<uint, gfx::PipelineState *> _PSOHashMap;
};

} // namespace pipeline
} // namespace cc
