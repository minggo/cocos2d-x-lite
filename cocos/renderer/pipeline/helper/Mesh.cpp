#include "Mesh.h"
#include "Pool.h"

namespace cc {
namespace pipeline {

uint8_t * Mesh::readIndices(uint primitiveIndex) {
    auto *data = GET_MESHDATA(dataIndex);
    if (!data || primitiveIndex >= meshStruct.subMeshPrimitiveCount) {
        return nullptr;
    }
    
    const auto *primitive = GET_SUB_MESH_PRIMITIVE(meshStruct.subMeshPrimitiveIndex, primitiveIndex);
    if (!primitive->indexView.count) {
        return nullptr;
    }
    
    return data + primitive->indexView.offset;
//    return new ctor(this._data.buffer, primitive.indexView.offset, primitive.indexView.count);
}

const FlatBufferList& RenderingSubMesh::flatBuffers() {
    if (_flatBuffers.size()) { return _flatBuffers; }
    if (!_mesh || _subMeshIdx == UINT_MAX) { return _flatBuffers; }

    const auto *primitive = GET_SUB_MESH_PRIMITIVE(_mesh->meshStruct.subMeshPrimitiveIndex, _subMeshIdx);
    auto idxCount = primitive->indexView.count;
    for (size_t i = 0; i < primitive->vertexBundleCount; i ++) {
        const auto *vertexBundle = GET_VERTEX_BUNDLES(_mesh->meshStruct.vertexBundlesIndex, i);
        const auto vbCount = primitive->indexView.count ? primitive->indexView.count : vertexBundle->view.count;
        const auto vbStride = vertexBundle->view.stride;
        const auto vbSize = vbStride * vbCount;
        uint8_t *view = GET_MESHDATA(_mesh->dataIndex) + vertexBundle->view.offset;
//        const view = new Uint8Array(mesh.data!.buffer, vertexBundle.view.offset, vertexBundle.view.length);
        if (!primitive->indexView.count) {
            FlatBuffer buffer = {vbStride, vbCount, vertexBundle->view.length, view};
            _flatBuffers.emplace_back(std::move(buffer));
            continue;
        }
        
        std::shared_ptr<uint8_t> vbView((uint8_t*)CC_MALLOC(vbSize), [&](uint8_t* ptr){CC_FREE(ptr);});
//        uint8_t *vbView = (uint8_t*)CC_MALLOC(vbSize);
        uint8_t *ibView = _mesh->readIndices(_subMeshIdx);
        // transform to flat buffer
        for (size_t n = 0; n < idxCount; ++n) {
            const auto idx = ibView[n];
            const auto offset = n * vbStride;
            const auto srcOffset = idx * vbStride;
            memcpy(vbView.get() + offset, view + srcOffset, vbStride);
        }
        FlatBuffer buffer = {vbStride, vbCount, vbSize, vbView.get()};
        _flatBuffers.emplace_back(std::move(buffer));
    }
    return _flatBuffers;
}
} //namespace pipeline
} //namespace cc
