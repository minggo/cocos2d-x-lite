#pragma once

#include "Define.h"

namespace cc {
class Root;

namespace scene {
struct Camera;
}

namespace pipeline {

class RenderFlow;
class RenderWindow;

struct CC_DLL RenderViewInfo {
    //TODO
};

class CC_DLL RenderView : public Object {
public:
    static void registerCreateFun(cc::Root *root);
    
    ~RenderView() = default;

    void destroy();
    void enable(bool value);
    bool initialize(const RenderViewInfo &info);
    void setExecuteFlows(const RenderFlowList &flows);
    void setPriority();

    CC_INLINE const String &getName() const { return _name; }
    CC_INLINE uint getPriority() const { return _priority; }
    CC_INLINE uint getVisibility() const { return _visibility; }
    CC_INLINE void setVisibility(uint value) { _visibility = value; }
    CC_INLINE scene::Camera *getCamera() const { return _camera; }
    CC_INLINE bool isEnabled() const { return _isEnabled; }
    CC_INLINE const RenderFlowList &getFlows() const { return _flows; }
    CC_INLINE const RenderWindow *getWindow() const { return _window; }
    // getWindow
    // setWindow

private:
    RenderView() = default;
    RenderView(cc::Root *root, scene::Camera *camera);

private:
    RenderWindow *_window = nullptr;
    RenderFlowList _flows;
    String _name;
    scene::Camera *_camera = nullptr;
    cc::Root *_root = nullptr;
    uint _priority = 0;
    uint _visibility = CAMERA_DEFAULT_MASK;
    bool _isEnabled = false;
};

} // namespace pipeline
} // namespace cc
