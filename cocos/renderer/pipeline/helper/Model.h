#pragma once
#include "core/CoreStd.h"

namespace cc {
namespace pipeline {

struct SubModel;

struct CC_DLL Model {
public:
    vector<SubModel *> subModels;
    
};

} //namespace pipeline
} //namespace cc
