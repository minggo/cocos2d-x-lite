#pragma once

#include "core/CoreStd.h"

namespace cc {

namespace scene {
struct Model;
struct SubModel;
}

namespace pipeline {

class RenderStage;
class RenderFlow;

enum class RenderFlowType : uint8_t {
    SCENE,
    POSTPROCESS,
    UI,
};

enum class CC_DLL RenderPriority : uint8_t {
    MIN = 0,
    MAX = 0xff,
    DEFAULT = 0x80,
};

struct CC_DLL RenderObject {
    scene::Model *model = nullptr;
    uint depth = 0;
};
typedef vector<struct RenderObject> RenderObjectList;

struct CC_DLL RenderTargetInfo {
    uint width = 0;
    uint height = 0;
};

struct CC_DLL RenderPass {
    uint hash = 0;
    uint depth = 0;
    uint shaderID = 0;
    uint index = 0;
    SubModel *subModel = nullptr;
};
typedef vector<RenderPass> RenderPassList;

typedef gfx::ColorAttachment ColorDesc;
typedef vector<ColorDesc> ColorDescList;

typedef gfx::DepthStencilAttachment DepthStencilDesc;

struct RenderPassDesc {
    uint index = 0;
    ColorDescList colorAttachments;
    DepthStencilDesc depthStencilAttachment;
};
typedef vector<RenderPassDesc> RenderPassDescList;

struct RenderTextureDesc {
    String name;
    gfx::TextureType type = gfx::TextureType::TEX2D;
    gfx::TextureUsage usage = gfx::TextureUsage::COLOR_ATTACHMENT;
    gfx::Format format = gfx::Format::UNKNOWN;
    int width = -1;
    int height = -1;
};
typedef vector<RenderTextureDesc> RenderTextureDescList;

struct FrameBufferDesc {
    String name;
    uint renderPass = 0;
    vector<String> colorTextures;
    String depthStencilTexture;
};
typedef vector<FrameBufferDesc> FrameBufferDescList;

enum class RenderFlowType : uint8_t {
    SCENE,
    POSTPROCESS,
    UI,
};

typedef vector<RenderStage *> RenderStageList;
typedef vector<RenderFlow *> RenderFlowList;
typedef vector<gfx::CommandBuffer *> CommandBufferList;

enum class RenderPassStage : uint8_t {
    DEFAULT = 100,
    UI = 200,
};

//TODO
const uint CAMERA_DEFAULT_MASK = 1;
//constexpr CAMERA_DEFAULT_MASK = Layers.makeMaskExclude([Layers.BitMask.UI_2D, Layers.BitMask.GIZMOS, Layers.BitMask.EDITOR,
//                                                           Layers.BitMask.SCENE_GIZMO, Layers.BitMask.PROFILER]);

class CC_DLL PassPhase {
public:
    static uint getPhaseID(const String &phaseName) {
        if(phases.find(phaseName) == phases.end()) {
            phases[phaseName] = 1 << phaseNum++;
        }
        return phases[phaseName];
    }
    
private:
    static map<String, uint> phases;
    static uint phaseNum;
};
map<String, uint> PassPhase::phases;
uint PassPhase::phaseNum = 0;

} // namespace pipeline
} // namespace cc
