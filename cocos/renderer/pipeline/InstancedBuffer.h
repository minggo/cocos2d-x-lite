#pragma once

#include "Define.h"

namespace cc {

namespace pipeline {

struct Pass;
struct PSOInfo;
struct SubModel;
struct InstancedAttributeBlock;

struct CC_DLL InstancedItem {
    gfx::Buffer *vb = nullptr;
    uint8_t *data = nullptr;
    uint dataSize = 0;
    gfx::InputAssembler *ia = nullptr;
    uint count = 0;
    uint capacity = 0;
    uint stride = 0;
};
typedef vector<InstancedItem> InstancedItemList;

class InstancedBuffer : public Object {
public:
    static const uint INITIAL_CAPACITY = 32;
    static const uint MAX_CAPACITY = 1024;
    
    static InstancedBuffer* get(Pass *pass);

    InstancedBuffer(Pass *pass);
    ~InstancedBuffer();

    void destroy();
    void merge(const SubModel *, const InstancedAttributeBlock &, const PSOInfo *);
    void uploadBuffers();
    void clear();

    CC_INLINE const InstancedItemList &getInstances() const { return _instancedItems; }
    //    CC_INLINE const cc::PSOCreateInfo &getPSOCreateInfo() const { return _PSOCreateInfo; }
    CC_INLINE Pass *getPass() const { return _pass; }
    

private:
    InstancedItemList _instancedItems;
    const PSOInfo *_psoci = nullptr;
    Pass *_pass = nullptr;
    static map<Pass*, InstancedBuffer*> _buffers;
};

} // namespace pipeline
} // namespace cc
