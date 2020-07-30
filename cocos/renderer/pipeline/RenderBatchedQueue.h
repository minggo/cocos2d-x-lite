#pragma once

#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

class BatchedBuffer;

class CC_DLL RenderBatchedQueue : public Object {
public:
    RenderBatchedQueue();
    ~RenderBatchedQueue() = default;

    void clear();
    void recordCommandBuffer(gfx::Device *, gfx::RenderPass *, gfx::CommandBuffer *);

    CC_INLINE set<BatchedBuffer *> &getQueue() { return _queue; }

private:
    set<BatchedBuffer *> _queue;
};

} // namespace pipeline
} // namespace cc
