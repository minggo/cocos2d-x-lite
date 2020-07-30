#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {
struct SubModel;
struct PSOInfo;
struct Pass;
struct Model;
struct InstancedAttribute;
class RenderingSubMesh;
namespace mesh {
struct VertexBundle;
struct SubMesh;

}

#define GET_MODEL(index) ModelPool::getModel(index)
#define GET_SUBMODEL(index, slot) SubModelPool::getSubModel(index, slot)
#define GET_PASS(index, slot) PassPool::getPass(index, slot)
#define GET_DEVICE(index) DevicePool::getDevice(index)
#define GET_PSOINFO(index) PSOInfoPool::getPSOInfo(index)
#define GET_PSOCI(index, slot) PSOInfoPool::getPSOInfo(index, slot)
#define GET_IA(index) InputAssemblerPool::getInputAssembler(index)
#define GET_BUFFER(index) BufferPool::getBuffer(index)
#define GET_BUFFERVIEW(index) BufferViewPool::getBufferView(index)
#define GET_INSTANCE_ATTRIBUTE(index) InstancedAttributePool::getInstanceAttribute(index)
#define GET_STRING(index) StringPool::getString(index)
#define GET_SUB_MESH_DATA(index) SubMeshPool::getSubMsh(index)
#define GET_MESHDATA(index) MeshDataPool::getMeshData(index)
#define GET_VERTEX_BUNDLES(index, slot) VertexBundlePool::getVertexBundle(index, slot)
#define GET_SUB_MESH_PRIMITIVE(index, slot) SubMeshPrimitivePool::getSubMeshPrimitive(index, slot)
#define GET_BINDING_LAYOUT(index) BindingLayoutPool::getBindingLayout(index)

class CC_DLL SubMeshPrimitivePool {
public:
    static mesh::SubMesh* getSubMeshPrimitive(uint index, uint slot);
};
class CC_DLL VertexBundlePool {
public:
    static mesh::VertexBundle* getVertexBundle(uint index, uint slot);
};

class CC_DLL MeshDataPool {
public:
    static uint8_t* getMeshData(uint index);
};

class CC_DLL PassPool {
public:
    static Pass* getPass(uint index);
    static Pass* getPass(uint index, uint slot);
};

class CC_DLL ModelPool {
public:
    static Model* getModel(uint index);
};

class CC_DLL SubModelPool {
public:
    static SubModel* getSubModel(uint index);
    static SubModel* getSubModel(uint index, uint slot);
};

class CC_DLL PSOInfoPool {
public:
    static PSOInfo* getPSOInfo(uint index);
    static PSOInfo* getPSOInfo(uint index, uint slot);
};

class CC_DLL BlendTargetPool {
public:
    static gfx::BlendTargetList getBlendTarget(uint index, uint count);
};

class CC_DLL ShaderPool {
public:
    static gfx::Shader* getShader(uint index);
};

class CC_DLL InputAssemblerPool {
public:
    static gfx::InputAssembler* getInputAssembler(uint index);
};

class CC_DLL DynamicStatePool {
public:
    static gfx::DynamicStateList getDynamicStates(uint index, uint count);
};

class CC_DLL BindingLayoutPool {
public:
    static gfx::BindingLayout* getBindingLayout(uint index);
};

class CC_DLL DevicePool {
public:
    static gfx::Device *getDevice(uint index);
};

class CC_DLL BufferPool {
public:
    static gfx::Buffer *getBuffer(uint index);
};

class CC_DLL BufferViewPool {
public:
    static uint8_t *getBufferView(uint index);
};

class CC_DLL InstancedAttributePool {
public:
    static InstancedAttribute* getInstanceAttribute(uint index);
};

class CC_DLL StringPool {
public:
    static String& getString(uint index);
};

class CC_DLL SubMeshPool {
public:
    static RenderingSubMesh* getSubMsh(uint index);
};

} //namespace pipeline
} //namespace cc
