#pragma once

#include "core/CoreStd.h"

namespace cc {

namespace gfx {
class Device;
class InputAssembler;
class PipelineState;
class RenderPass;
};

namespace pipeline {

struct PSOInfo;

class CC_DLL PipelineStateManager {
public:
    static gfx::PipelineState *getOrCreatePipelineStage(gfx::Device *device,
                                                        const PSOInfo *PSOInfo,
                                                        gfx::RenderPass *renderPass,
                                                        gfx::InputAssembler *inputAssembler);
    
private:
    static map<uint, gfx::PipelineState *> _PSOHashMap;
};

} // namespace pipeline
} // namespace cc
