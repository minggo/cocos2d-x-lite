#pragma once

#include "Define.h"

namespace cc {
namespace pipeline {

struct Pass;
struct SubModel;
struct PSOInfo;

struct CC_DLL BatchedItem {
    gfx::BufferList vbs;
    vector<std::shared_ptr<uint8_t>> vbDatas;
    gfx::Buffer *vbIdx = nullptr;
    vector<float> vbIdxData;
    uint vbCount = 0;
    uint mergCount = 0;
    gfx::InputAssembler *ia = nullptr;
    gfx::Buffer *ubo = nullptr;
    UBOLocalBatched uboData;
    PSOInfo *psoInfo = nullptr;
};
typedef vector<BatchedItem> BatchedItemList;

class CC_DLL BatchedBuffer : public Object {
public:
    BatchedBuffer(Pass *pass);
    ~BatchedBuffer() = default;
    
    static BatchedBuffer *get(Pass *pass);

    void destroy();
    void merge(const SubModel *, uint passIdx, const RenderObject&);
    void clear();
    void clearUBO();

    CC_INLINE const BatchedItemList &getBaches() const { return _batchedItems; }
    CC_INLINE Pass *getPass() const { return _pass; }

private:
    //    const _localBatched = new UBOLocalBatched();
    BatchedItemList _batchedItems;
    Pass *_pass = nullptr;
    static map<Pass*, BatchedBuffer*> _buffers;
};

} // namespace pipeline
} // namespace cc
