#pragma once

#include "core/CoreStd.h"

namespace cc {
class Light;
class RenderObject;
struct MacroPatch;

namespace pipeline {

struct SubModel;
struct Pass;
struct PSOCreateInfo;

class RenderAdditiveLightQueue : public Object {
public:
    RenderAdditiveLightQueue();
    ~RenderAdditiveLightQueue() = default;
    
    void add(RenderObject *renderObj, uint subModelIdx, Pass *pass, uint beginIdx, uint endIdx);
    void clear(const vector<Light *> &validLights,
               const vector<gfx::Buffer *> &lightBuffers,
               const vector<uint> &lightIndices);
    void recordCommandBuffer(gfx::Device *device, gfx::RenderPass *renderPass, gfx::CommandBuffer *cmdBuff);
    
private:
    void attach(RenderObject *renderObj, uint subModelIdx, gfx::Buffer *lightBuffer,
                uint lightIdx, Pass *pass, vector<MacroPatch> patches);

private:
    vector<vector<SubModel *>> _sortedSubModelsArray;
    vector<vector<PSOCreateInfo>> _sortedPSOCIArray;
    vector<Light *> _validLights;
    vector<gfx::Buffer *> _lightBuffers;
    vector<uint> _lightIndices;
    uint _phaseID = 0;
};

} // namespace pipeline
} // namespace cc
