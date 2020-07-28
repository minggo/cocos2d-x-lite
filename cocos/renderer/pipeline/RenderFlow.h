#pragma once

#include "Define.h"

namespace cc {
namespace pipeline {

class RenderPipeline;
class RenderStage;
class RenderView;
class Material;

struct CC_DLL RenderFlowInfo {
    String name;
    float priority = 0;
    Material *material = nullptr;
    RenderFlowType type;
};

class CC_DLL RenderFlow : public Object {
public:
    RenderFlow();
    virtual ~RenderFlow() = default;

    virtual bool initialize(const RenderFlowInfo &info);
    virtual void activate(RenderPipeline *pipeline);
    virtual void resize(uint width, uint height);
    virtual void render(RenderView *view);

    virtual void destroy() = 0;
    virtual void rebuild() = 0;

    void destroyStages();

    CC_INLINE const gfx::Device *getDevice() const { return _device; }
    CC_INLINE const RenderPipeline *getPipeline() const { return _pipeline; }
    CC_INLINE const String &getName() const { return _name; }
    CC_INLINE int getPriority() const { return _priority; }
    CC_INLINE const RenderStageList &getStages() const { return _stages; }
    //    CC_INLINE const Material *getMaterial() const { return _material; }
    CC_INLINE RenderFlowType getType() const { return _type; }

protected:
    void activateStages();

protected:
    gfx::Device *_device = nullptr;
    RenderPipeline *_pipeline = nullptr;
    String _name;
    int _priority = 0;
    RenderStageList _stages;
    Material *_material = nullptr;
    RenderFlowType _type = RenderFlowType::SCENE;
};

} // namespace pipeline
} // namespace cc
