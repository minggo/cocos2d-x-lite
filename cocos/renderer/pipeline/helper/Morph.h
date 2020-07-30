
#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {
namespace mesh {
struct BufferView;
} //namespace mesh

struct CC_DLL MorphTarget {
    vector<mesh::BufferView> displacements:
}
typedef vector<MorphTarget> MorphTargetList;

struct CC_DLL SubMeshMorph {
    vector<String> attributes;
    MorphTargetList targets;
    vector<uint> weights;
};

struct CC_DLL Morph {
    array<SubMeshMorph> subMeshMorphs;
    vector<uint> weights
};

} //namespace pipline
} //namespace cc
