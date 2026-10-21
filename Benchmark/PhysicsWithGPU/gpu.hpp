#pragma once

#include <cuda_runtime.h>
#include "Scene/Scene.hpp"
#include "ECS/Entity.hpp"
#include "Physics/Physics.hpp"

struct ObjectData
{
    unsigned int entityId;
    RigidBody rigidBody;
    Transform transform;
    bool hasTransform;
};

__global__ void Calculate (ObjectData *objectBuffer,float Gravity, float dt);

namespace GPU {
    inline float Gravity = -9.8;
    inline float dt = 0.1;

    void Update ();
}
