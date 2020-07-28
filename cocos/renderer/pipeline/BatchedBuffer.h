#pragma once

#include "Define.h"

namespace cc {
namespace pipeline {

struct Pass;
struct SubModel;
struct PSOInfo;


struct CC_DLL BatchedItem {
    gfx::BufferList vbs;
    uint8_t *vbDatas = nullptr;
    gfx::Buffer *vbIdx = nullptr;
    float *vbIdxData = nullptr;
    uint mergCount = 0;
    gfx::InputAssembler *ia = nullptr;
    gfx::Buffer *ubo = nullptr;
    PSOInfo *psoInfo = nullptr;
};
typedef vector<BatchedItem> BatchedItemList;

class CC_DLL BatchedBuffer : public Object {
public:
    BatchedBuffer(Pass *pass);
    ~BatchedBuffer() = default;

    void destroy();
    void merge(SubModel *, uint passIdx, RenderObject *);
    void clear();
    void clearUBO();

    CC_INLINE const BatchedItemList &getBaches() const { return _batchedItems; }
    CC_INLINE Pass *getPass() const { return _pass; }

private:
    //    const _localBatched = new UBOLocalBatched();
    BatchedItemList _batchedItems;
    Pass *_pass = nullptr;
};

} // namespace pipeline
} // namespace cc
