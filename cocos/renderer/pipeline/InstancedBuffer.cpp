#include "InstancedBuffer.h"
#include "helper/Pass.h"
#include "helper/Pool.h"
#include "helper/Model.h"
#include "helper/Pool.h"
#include "helper/SubModel.h"
#include "gfx/GFXInputAssembler.h"
#include "gfx/GFXBuffer.h"

namespace cc {
namespace pipeline {
map<Pass*, InstancedBuffer*> InstancedBuffer::_buffers;
InstancedBuffer* InstancedBuffer::get(Pass *pass) {
    if (_buffers.find(pass) == _buffers.end()) {
        _buffers[pass] = CC_NEW(InstancedBuffer(pass)); //TODO release
    }
    return _buffers[pass];
}

InstancedBuffer::InstancedBuffer(Pass *pass) {
    
}

InstancedBuffer::~InstancedBuffer() {
    destroy();
}

void InstancedBuffer::destroy() {
    
}

void InstancedBuffer::merge(const SubModel *subModel, const InstancedAttributeBlock &attrs, const PSOInfo *psoci) {
    const auto stride = attrs.bufferViewSize;
    if (!stride) { return; } // we assume per-instance attributes are always present
    if (!_psoci) { _psoci = psoci; }
    const auto *sourceIA = GET_IA(subModel->inputAssemblerIndex);
    for (size_t i = 0; i < _instancedItems.size(); ++i) {
        auto &instance = _instancedItems[i];
        if (instance.ia->getIndexBuffer() != sourceIA->getIndexBuffer() || instance.count >= MAX_CAPACITY) { continue; }
        if (instance.stride != stride) {
            // console.error(`instanced buffer stride mismatch! ${stride}/${instance.stride}`);
            return;
        }
        if (instance.count >= instance.capacity) { // resize buffers
            instance.capacity |= instance.capacity << 1;
            const auto newSize = instance.stride * instance.capacity;
            const auto *oldData = instance.data;
            const auto oldSize = instance.dataSize;
            instance.data = (uint8_t*)CC_MALLOC(newSize);
            memcpy(instance.data, oldData, oldSize);
            instance.dataSize = newSize;
            instance.vb->resize(newSize);
        }
        memcpy(instance.data + instance.stride * instance.count++, GET_BUFFERVIEW(attrs.bufferViewIndex), attrs.bufferViewSize);
        return;
    }

    //TODO coulsonwang
    // Create a new instance
    gfx::Buffer * vb = nullptr;
//    const vb = this._device.createBuffer({
//        usage: GFXBufferUsageBit.VERTEX | GFXBufferUsageBit.TRANSFER_DST,
//        memUsage: GFXMemoryUsageBit.HOST | GFXMemoryUsageBit.DEVICE,
//        size: stride * INITIAL_CAPACITY, stride,
//    });
    size_t dataSize = stride * INITIAL_CAPACITY;
//    uint8_t *data = (uint8_t*)CC_MALLOC(dataSize);
    std::shared_ptr<uint8_t> data((uint8_t*)CC_MALLOC(dataSize), [&](uint8_t* ptr){ CC_FREE(ptr);});
    auto vertexBuffers = sourceIA->getVertexBuffers();
    auto attributes = sourceIA->getAttributes();
    const auto *indexBuffer = sourceIA->getIndexBuffer();

    for (size_t i = 0; i < attrs.instancedAttributesCount; i++) {
        const auto *attr = GET_INSTANCE_ATTRIBUTE(attrs.instancedAttributesIndex);
        
        gfx::Attribute newAttr;
        newAttr.format = (gfx::Format)attr->format;
        newAttr.name = GET_STRING(attr->nameIndex);
        newAttr.stream = vertexBuffers.size();
        newAttr.isInstanced = true;
        if (attr->isNormalized) { newAttr.isNormalized = attr->isNormalized; }
        attributes.emplace_back(newAttr);
    }
    memcpy(data.get(), GET_BUFFERVIEW(attrs.bufferViewIndex), attrs.bufferViewSize);

    vertexBuffers.emplace_back(vb);
    //TODO coulsonwang
    gfx::InputAssembler* ia = nullptr;
//    const ia = this._device.createInputAssembler({ attributes, vertexBuffers, indexBuffer });
//    _instances.push({ count: 1, capacity: INITIAL_CAPACITY, vb, data, ia, stride });
    InstancedItem item;
    item.vb = vb;
    item.data = data.get();
    item.dataSize = dataSize;
    item.ia = ia;
    item.count = 1;
    item.capacity = INITIAL_CAPACITY;
    item.stride = stride;
    _instancedItems.emplace_back(std::move(item));
}

} // namespace pipeline
} // namespace cc
