#include "ForwardStage.h"
#include "../RenderBatchedQueue.h"
#include "../RenderInstancedQueue.h"
#include "../RenderAdditiveLightQueue.h"
#include "../RenderQueue.h"
#include "../helper/SubModel.h"


namespace cc {
namespace pipeline {

//const RenderStageInfo &ForwardStage::getInitializeInfo() {
//
//}

ForwardStage::ForwardStage() : RenderStage(){
    _batchedQueue = CC_NEW(RenderBatchedQueue);
    _instancedQueue = CC_NEW(RenderInstancedQueue);
    _additiveLightQueue = CC_NEW(RenderAdditiveLightQueue);
}

ForwardStage::~ForwardStage() {
    destroy();
}

void ForwardStage::activate(RenderFlow *flow) {
    RenderStage::activate(flow);
}

void ForwardStage::destroy() {
    CC_SAFE_DELETE(_batchedQueue);
    CC_SAFE_DELETE(_instancedQueue);
    CC_SAFE_DELETE(_additiveLightQueue);
    for(auto *renderQueue : _renderQueues) {
        CC_SAFE_DELETE(renderQueue);
    }
    _renderQueues.clear();
}

void ForwardStage::resize(uint width, uint height) {
}

void ForwardStage::rebuild() {
}

void ForwardStage::render(RenderView *view) {
}

} // namespace pipeline
} // namespace cc
