#pragma once

#include "Define.h"

namespace cc {
struct InstancedAttributeBlock;


namespace scene {
struct Pass;
struct PSOCreateInfo;
struct SubModel;
}

namespace pipeline {

struct CC_DLL InstancedItem {
    gfx::Buffer *vb = nullptr;
    uint8_t *data = nullptr;
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

    InstancedBuffer(scene::Pass *pass);
    ~InstancedBuffer() = default;

    void destroy();
    void merge(scene::SubModel *, const cc::InstancedAttributeBlock &, const scene::PSOCreateInfo &);
    void uploadBuffers();
    void clear();

    CC_INLINE const InstancedItemList &getInstances() const { return _instancedItems; }
    //    CC_INLINE const cc::PSOCreateInfo &getPSOCreateInfo() const { return _PSOCreateInfo; }
    CC_INLINE scene::Pass *getPass() const { return _pass; }

private:
    InstancedItemList _instancedItems;
    //    cc::PSOCreateInfo _PSOCreateInfo;
    scene::Pass *_pass = nullptr;
};

} // namespace pipeline
} // namespace cc
