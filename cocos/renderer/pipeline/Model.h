#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace scene {

struct SubModel;

struct CC_DLL Model {
public:
    vector<SubModel *> subModels;
    
};

} //namespace renderer
} //namespace cc
