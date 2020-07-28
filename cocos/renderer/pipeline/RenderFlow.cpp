#include "RenderFlow.h"
#include "RenderStage.h"

namespace cc {
namespace pipeline {

RenderFlow::RenderFlow() : GFXObject(gfx::ObjectType::RENDER_FLOW) {
}

bool RenderFlow::initialize(const RenderFlowInfo &info) {
    _name = info.name;
    _priority = info.priority;
    _material = info.material;
    _type = info.type;
    
    return true;
}

void RenderFlow::activate(RenderPipeline *pipeline) {
    _pipeline = pipeline;
    activateStages();
}

void RenderFlow::resize(uint width, uint height) {
    for(auto * stage : _stages) {
        stage->resize(width, height);
    }
}

void RenderFlow::render(RenderView *view) {
    for(auto *stage : _stages) {
        stage->render(view);
    }
}

void RenderFlow::activateStages() {
    for (auto *stage : _stages) {
        stage->activate(this);
    }
    
    std::sort(_stages.begin(), _stages.end(), [](const auto* a, const auto *b){
        return a->getPriority() - b->getPriority();
    });
}

} //namespace pipeline
} // namespace cc
