#pragma once

#include "../RenderPipeline.h"

namespace cc {
namespace pipeline {

class CC_DLL ForwardPipeline : public RenderPipeline {
public:
    ForwardPipeline();
    ~ForwardPipeline();

    virtual bool initialize(const RenderPipelineInfo &info) override;
    virtual void destroy() override;
    virtual bool activate() override;
    virtual void rebuild() override;
    virtual void updateUBOs(RenderView *view) override;
    virtual void sceneCulling() override;
    virtual vector<float> &getLightIndices() const override;
    virtual vector<float> &getLightIndexOffsets() const override;
    virtual vector<gfx::Buffer *> &getLightBuffers() const override;

    CC_INLINE gfx::Buffer *getLightsUBO() { return _lightsUBO; }

private:
    void cullLightPerModel(Model *model);

private:
    gfx::Buffer *_lightsUBO = nullptr;
};

} // namespace pipeline
} // namespace cc
