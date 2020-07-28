#pragma once

#include "Define.h"

namespace cc {

namespace gfx {
class Framebuffer;
} // namespace gfx

namespace pipeline {

class RenderFlow;
class RenderPipeline;
class RenderView;
class RenderQueue;

enum class RenderQueueSortMode : uint8_t {
    FRONT_TO_BACK,
    BACK_TO_FRONT
};

struct CC_DLL RenderQueueDescriptor {
    bool isTransparent = false;
    RenderQueueSortMode sortMode = RenderQueueSortMode::FRONT_TO_BACK;
    vector<String> stages;
};
typedef vector<RenderQueueDescriptor> RenderQueueDescptorList;

struct CC_DLL RenderStageInfo {
    String name;
    uint priority = 0;
    RenderQueueDescptorList renderQueues;
    String framebuffer;
};

class CC_DLL RenderStage : public Object {
public:
    RenderStage();
    virtual ~RenderStage() = default;

    virtual void activate(RenderFlow *flow);
    virtual bool initialize(const RenderStageInfo &info);

    virtual void destroy() = 0;
    virtual void rebuild() = 0;
    virtual void render(RenderView *view) = 0;
    virtual void resize(uint width, uint height) = 0;

    void createBuffer();
    void executeCommandBuffer(RenderView *view);
    void setClearColor(const gfx::Color &color);
    void setClearColors(const gfx::ColorList &colors);
    void setClearDepth(float depth);
    void setClearStencil(uint stencil);
    void setRenderArea(size_t width, size_t height);
    void sortRenderQueue();

    CC_INLINE RenderFlow *getFlow() const { return _flow; }
    CC_INLINE gfx::Framebuffer *getFrameBuffer() const { return _framebuffer; }
    CC_INLINE const RenderPipeline *getPipeline() const { return _pipeline; }
    CC_INLINE int getPriority() const { return _priority; }

protected:
    RenderFlow *_flow = nullptr;
    const RenderPipeline *_pipeline = nullptr;
    gfx::Framebuffer *_framebuffer = nullptr;
    int _priority = 0;
    String _name;
    String _framebufferName;
    vector<gfx::Color> _clearColors;
    gfx::Rect _renderArea;
    RenderQueueDescptorList _renderQueueDescriptors;
    vector<RenderQueue *> _renderQueues;
    float _clearDepth = 1.0f;
    uint _clearStencil = 0;
};

} // namespace pipeline
} // namespace cc
