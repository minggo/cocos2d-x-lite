#pragma once

#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct Model;
struct SubModel;
class RenderStage;
class RenderFlow;

enum class CC_DLL RenderPriority : uint8_t {
    MIN = 0,
    MAX = 0xff,
    DEFAULT = 0x80,
};

struct CC_DLL RenderObject {
    uint modelIndex = 0; //Model *
    uint depth = 0;
};
typedef vector<RenderObject> RenderObjectList;

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
struct CC_DLL RenderPassDesc {
    uint index = 0;
    ColorDescList colorAttachments;
    DepthStencilDesc depthStencilAttachment;
};
typedef vector<RenderPassDesc> RenderPassDescList;

struct CC_DLL RenderTextureDesc {
    String name;
    gfx::TextureType type = gfx::TextureType::TEX2D;
    gfx::TextureUsage usage = gfx::TextureUsage::COLOR_ATTACHMENT;
    gfx::Format format = gfx::Format::UNKNOWN;
    int width = -1;
    int height = -1;
};
typedef vector<RenderTextureDesc> RenderTextureDescList;

struct CC_DLL FrameBufferDesc {
    String name;
    uint renderPass = 0;
    vector<String> colorTextures;
    String depthStencilTexture;
};
typedef vector<FrameBufferDesc> FrameBufferDescList;

enum class CC_DLL RenderFlowType : uint8_t {
    SCENE,
    POSTPROCESS,
    UI,
};

typedef vector<RenderStage *> RenderStageList;
typedef vector<RenderFlow *> RenderFlowList;
typedef vector<gfx::CommandBuffer *> CommandBufferList;

enum class CC_DLL RenderPassStage : uint8_t {
    DEFAULT = 100,
    UI = 200,
};

//TODO
const uint CC_DLL CAMERA_DEFAULT_MASK = 1;
//constexpr CAMERA_DEFAULT_MASK = Layers.makeMaskExclude([Layers.BitMask.UI_2D, Layers.BitMask.GIZMOS, Layers.BitMask.EDITOR,
//                                                           Layers.BitMask.SCENE_GIZMO, Layers.BitMask.PROFILER]);

struct CC_DLL RenderQueueDesc {
    bool isTransparent = false;
    uint phases = 0;
    std::function<size_t(const RenderPass &a, const RenderPass &b)> sortFunc;
};

#define MAX_BINDING_SUPPORTED (24)
enum class CC_DLL UniformBinding : uint8_t {
    // UBOs
    UBO_GLOBAL = MAX_BINDING_SUPPORTED - 1,
    UBO_SHADOW = MAX_BINDING_SUPPORTED - 2,

    UBO_LOCAL = MAX_BINDING_SUPPORTED - 3,
    UBO_FORWARD_LIGHTS = MAX_BINDING_SUPPORTED - 4,
    UBO_SKINNING_ANIMATION = MAX_BINDING_SUPPORTED - 5,
    UBO_SKINNING_TEXTURE = MAX_BINDING_SUPPORTED - 6,
    UBO_UI = MAX_BINDING_SUPPORTED - 7,
    UBO_MORPH = MAX_BINDING_SUPPORTED - 8,
    UBO_PCF_SHADOW = MAX_BINDING_SUPPORTED - 9,
    UBO_BUILTIN_BINDING_END = MAX_BINDING_SUPPORTED - 10,

    // samplers
    SAMPLER_JOINTS = MAX_BINDING_SUPPORTED + 1,
    SAMPLER_ENVIRONMENT = MAX_BINDING_SUPPORTED + 2,
    SAMPLER_MORPH_POSITION = MAX_BINDING_SUPPORTED + 3,
    SAMPLER_MORPH_NORMAL = MAX_BINDING_SUPPORTED + 4,
    SAMPLER_MORPH_TANGENT = MAX_BINDING_SUPPORTED + 5,
    SAMPLER_LIGHTING_MAP = MAX_BINDING_SUPPORTED + 6,
    SAMPLER_SHADOWMAP = MAX_BINDING_SUPPORTED + 7,

    // rooms left for custom bindings
    // effect importer prepares bindings according to this
    CUSTUM_UBO_BINDING_END_POINT = UBO_BUILTIN_BINDING_END,
    CUSTOM_SAMPLER_BINDING_START_POINT = MAX_BINDING_SUPPORTED + 8,
};

struct CC_DLL UBOLocalBatched {
    static const uint BATCHING_COUNT = 10;
    static const uint MAT_WORLDS_OFFSET = 0;
    static const uint COUNT = 16 * BATCHING_COUNT;
    static const uint SIZE = COUNT * 4;
    static gfx::UniformBlock BLOCK;

    std::array<float, UBOLocalBatched::COUNT> view;
    //view: Float32Array = new Float32Array(UBOLocalBatched.COUNT);
};
gfx::UniformBlock UBOLocalBatched::BLOCK = {
    gfx::ShaderType::VERTEX,
    (uint)UniformBinding::UBO_LOCAL,
    "CCLocalBatched",
    {{ "cc_matWorlds", gfx::Type::MAT4, (uint)UBOLocalBatched::BATCHING_COUNT }}
};

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
