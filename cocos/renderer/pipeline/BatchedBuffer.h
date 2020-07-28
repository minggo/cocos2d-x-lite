#pragma once

#include "Define.h"

namespace cc {

namespace scene {
struct Pass;
struct SubModel;
struct PSOCreateInfo;
}

namespace pipeline {

struct CC_DLL BatchedItem {
    gfx::BufferList vbs;
    uint8_t *vbDatas = nullptr;
    gfx::Buffer *vbIdx = nullptr;
    float *vbIdxData = nullptr;
    uint mergCount = 0;
    gfx::InputAssembler *ia = nullptr;
    gfx::Buffer *ubo = nullptr;
    scene::PSOCreateInfo *psoCreatedInfo = nullptr;
};
typedef vector<BatchedItem> BatchedItemList;

class CC_DLL BatchedBuffer : public Object {
public:
    BatchedBuffer(scene::Pass *pass);
    ~BatchedBuffer() = default;

    void destroy();
    void merge(scene::SubModel *, uint passIdx, RenderObject *);
    void clear();
    void clearUBO();

    CC_INLINE const BatchedItemList &getBaches() const { return _batchedItems; }
    CC_INLINE scene::Pass *getPass() const { return _pass; }

private:
    //    const _localBatched = new UBOLocalBatched();
    BatchedItemList _batchedItems;
    scene::Pass *_pass = nullptr;
};

} // namespace pipeline
} // namespace cc
