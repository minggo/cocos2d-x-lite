#pragma once

#include "core/CoreStd.h"
#include "math/Vec3.h"

namespace cc {
namespace pipeline {

struct Morph;

namespace mesh {
struct BufferView {
    uint offset = 0;
    uint length = 0;
    uint count = 0;
    uint stride = 0;
};

struct VertexBundle {
    BufferView view;
    gfx::AttributeList attributes;
};
typedef vector<VertexBundle> VertexBundleList;

struct SubMesh {
    uint vertexBundleIndices = 0;//vector<uint> vertexBundelIndices;
    uint vertexBundleCount = 0;
    
    gfx::PrimitiveMode primitiveMode;
    BufferView indexView;
    uint jointMapIndex;
};
typedef vector<SubMesh> SubMeshList;

struct MeshStruct {
    uint vertexBundlesIndex = 0;//VertexBundleList vertexBundles;
    uint vertexBundlesCount = 0;
    
    uint subMeshPrimitiveIndex = 0;//SubMeshList primitives;
    uint subMeshPrimitiveCount = 0;
    
    Vec3 minPosition;
    Vec3 maxPosition;
    uint jointMapsIndex;//vector<vector<int>>jointMaps;
    uint morphIndex;//Morph *morph = nullptr;
};
} //namespace mesh

struct CC_DLL Mesh {
    uint loaded = 0;
    mesh::MeshStruct meshStruct;
    uint dataIndex = 0;
//    uint8_t *data = nullptr; //
    
    uint8_t * readIndices(uint primitiveIndex);
};

struct CC_DLL FlatBuffer {
    uint stride = 0;
    uint count = 0;
    uint size = 0;
    uint8_t *buffer = nullptr;
};
typedef vector<FlatBuffer> FlatBufferList;

class CC_DLL RenderingSubMesh : public Object {
public:
    const FlatBufferList& flatBuffers();
    
private:
    FlatBufferList _flatBuffers;
    Mesh *_mesh = nullptr;
    uint _subMeshIdx = UINT_MAX;
};

} //namespace pipeline
} //namespace cc
