#include "BatchedBuffer.h"
#include "helper/Pool.h"
#include "helper/SubModel.h"
#include "helper/Mesh.h"
#include "helper/Model.h"
#include "gfx/GFXBuffer.h"
#include "gfx/GFXInputAssembler.h"
#include "gfx/GFXBindingLayout.h"

namespace cc {
namespace pipeline {

map<Pass*, BatchedBuffer*> BatchedBuffer::_buffers;
BatchedBuffer* BatchedBuffer::get(Pass *pass) {
    if(_buffers.find(pass) == _buffers.end()) {
        _buffers[pass] = CC_NEW(BatchedBuffer(pass));
    }
    return _buffers[pass];
}

void BatchedBuffer::merge(const SubModel *subModel, uint passIdx, const RenderObject& ro) {
    const auto &flatBuffers = GET_SUB_MESH_DATA(subModel->subMeshIndex)->flatBuffers(); //subModel->subMeshData.flatBuffers();
    if (flatBuffers.size() == 0) { return; }
    size_t vbSize = 0;
    size_t vbIdxSize = 0;
    const auto vbCount = flatBuffers[0].count;
    const auto *psoCreateInfo = GET_PSOCI(subModel->psoInfosIndex, passIdx);
    auto *bindingLayout = GET_BINDING_LAYOUT(psoCreateInfo->bindingLayoutIndex);
    bool isBatchExist = false;
    for (size_t i = 0; i < _batchedItems.size(); ++i) {
//        const batch = this.batches[i];
//        if (batch.vbs.length === flatBuffers.length && batch.mergeCount < UBOLocalBatched.BATCHING_COUNT) {
//            isBatchExist = true;
//            for (let j = 0; j < batch.vbs.length; ++j) {
//                const vb = batch.vbs[j];
//                if (vb.stride !== flatBuffers[j].stride) {
//                    isBatchExist = false;
//                    break;
//                }
//            }
//
//            if (isBatchExist) {
//                for (let j = 0; j < batch.vbs.length; ++j) {
//                    const flatBuff = flatBuffers[j];
//                    const batchVB = batch.vbs[j];
//                    const vbBuf = batch.vbDatas[j];
//                    vbSize = (vbCount + batch.vbCount) * flatBuff.stride;
//                    if (vbSize > batchVB.size) {
//                        batchVB.resize(vbSize);
//                        batch.vbDatas[j] = new Uint8Array(vbSize);
//                        batch.vbDatas[j].set(vbBuf);
//                    }
//                    batch.vbDatas[j].set(flatBuff.buffer, batch.vbCount * flatBuff.stride);
//                }
//
//                let vbIdxBuf = batch.vbIdxData;
//                vbIdxSize = (vbCount + batch.vbCount) * 4;
//                if (vbIdxSize > batch.vbIdx.size) {
//                    batch.vbIdx.resize(vbIdxSize);
//                    batch.vbIdxData = new Float32Array(vbIdxSize / Float32Array.BYTES_PER_ELEMENT);
//                    batch.vbIdxData.set(vbIdxBuf);
//                    vbIdxBuf = batch.vbIdxData;
//                }
//
//                const start = batch.vbCount;
//                const end = start + vbCount;
//                const mergeCount = batch.mergeCount;
//                if (vbIdxBuf[start] !== mergeCount || vbIdxBuf[end - 1] !== mergeCount) {
//                    for (let j = start; j < end; j++) {
//                        vbIdxBuf[j] = mergeCount + 0.1; // guard against underflow
//                    }
//                }
//
//                // update world matrix
//                Mat4.toArray(batch.uboData.view, ro.model.transform.worldMatrix, UBOLocalBatched.MAT_WORLDS_OFFSET + batch.mergeCount * 16);
//                if (!batch.mergeCount && batch.psoCreateInfo !== psoCreateInfo) {
//                    bindingLayout.bindBuffer(UBOLocalBatched.BLOCK.binding, batch.ubo);
//                    bindingLayout.update();
//                    batch.psoCreateInfo = psoCreateInfo;
//                }
//
//                ++batch.mergeCount;
//                batch.vbCount += vbCount;
//                batch.ia.vertexCount += vbCount;
//
//                return;
//            }
//        }
    }
//
    // Create a new batch
    vector<gfx::Buffer*> vbs;
    vector<std::shared_ptr<uint8_t>> vbDatas;
    vector<gfx::Buffer*> totalVBs;
    for (size_t i = 0; i < flatBuffers.size(); ++i) {
        const auto &flatBuff = flatBuffers[i];
        gfx::Buffer *newVB = nullptr;
        //TODO coulsonwang
//        const newVB = this._device.createBuffer({
//            usage: GFXBufferUsageBit.VERTEX | GFXBufferUsageBit.TRANSFER_DST,
//            memUsage: GFXMemoryUsageBit.HOST | GFXMemoryUsageBit.DEVICE,
//            size: flatBuff.count * flatBuff.stride,
//            stride: flatBuff.stride,
//        });
        newVB->update(flatBuff.buffer, 0, flatBuff.size);
        vbs.emplace_back(newVB);
        std::shared_ptr<uint8_t> vbData((uint8_t*)CC_MALLOC(newVB->getSize()), [&](uint8_t *ptr){CC_FREE(ptr);});
        vbDatas.emplace_back(vbData);
        totalVBs.emplace_back(newVB);
    }
    
    gfx::Buffer *vbIdx = nullptr;
    //TODO coulsonwang
//    const vbIdx = this._device.createBuffer({
//        usage: GFXBufferUsageBit.VERTEX | GFXBufferUsageBit.TRANSFER_DST,
//        memUsage: GFXMemoryUsageBit.HOST | GFXMemoryUsageBit.DEVICE,
//        size: vbCount * 4,
//        stride: 4,
//    });
    vector<float> vbIdxData(vbCount, 0);
    vbIdx->update(vbIdxData.data(), 0, vbIdxData.size());
    totalVBs.emplace_back(vbIdx);

    const auto &attributes = GET_IA(subModel->inputAssemblerIndex)->getAttributes();
    auto attrs = attributes;
    gfx::Attribute batchID;
    batchID.name = "a_dyn_batch_id";
    batchID.format = gfx::Format::R32F;
    batchID.stream = flatBuffers.size();
    attrs.emplace_back(std::move(batchID));

    gfx::InputAssembler *ia = nullptr;
    //TODO coulsonwang
//    const ia = this._device.createInputAssembler({
//        attributes: attrs,
//        vertexBuffers: totalVBs,
//    });
    
    gfx::Buffer * ubo = nullptr;
    //TODO coulsonwang
//    const ubo = this._device.createBuffer({
//        usage: GFXBufferUsageBit.UNIFORM | GFXBufferUsageBit.TRANSFER_DST,
//        memUsage: GFXMemoryUsageBit.HOST | GFXMemoryUsageBit.DEVICE,
//        size: UBOLocalBatched.SIZE,
//    });

    bindingLayout->bindBuffer(UBOLocalBatched::BLOCK.binding, ubo);
    bindingLayout->update();

    UBOLocalBatched uboData;
    const auto &worldMatrix = GET_MODEL(ro.modelIndex)->worldMatrix;
    memcpy(UBOLocalBatched::view.data() + UBOLocalBatched::MAT_WORLDS_OFFSET, worldMatrix.m, sizeof(worldMatrix));

    BatchedItem item;
    item.mergCount = 1;
    item.vbs = std::move(vbs);
    item.vbDatas = std::move(vbDatas);
    item.vbIdx = vbIdx;
    item.vbCount = vbCount;
    item.ia = ia;
    item.ubo = ubo;
//    item.uboData = uboData;
//    item.vbIdxData = std::move(vbIdxData);
//    _batchedItems.emplace_back(<#_Args &&__args...#>);
//    .push({
//        mergeCount: 1,
//        vbs, vbDatas, vbIdx, vbIdxData, vbCount, ia, ubo, uboData, psoCreateInfo,
//    });
}

} // namespace pipeline
} // namespace cc
