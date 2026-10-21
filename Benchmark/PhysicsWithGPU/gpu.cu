#include <cuda_runtime.h>
#include "Scene/Scene.hpp"
#include "ECS/Entity.hpp"
#include "Physics/Physics.hpp"
#include "gpu.hpp"

__global__ void Calculate (ObjectData *objectBuffer,float Gravity, float dt)
{
    size_t Idx = threadIdx.x + blockDim.x * blockIdx.x;
    objectBuffer[Idx].rigidBody.Force.y += Gravity;

    if (objectBuffer[Idx].hasTransform && objectBuffer[Idx].transform.Active)
    {
        objectBuffer[Idx].transform.Position.x += objectBuffer[Idx].rigidBody.Velocity.x * dt + objectBuffer[Idx].rigidBody.Mass * 0.5f * dt * dt;
        objectBuffer[Idx].transform.Position.y += objectBuffer[Idx].rigidBody.Velocity.y * dt + objectBuffer[Idx].rigidBody.Mass * 0.5f * dt * dt;
        objectBuffer[Idx].transform.Position.z += objectBuffer[Idx].rigidBody.Velocity.z * dt + objectBuffer[Idx].rigidBody.Mass * 0.5f * dt * dt;
    }

    objectBuffer[Idx].rigidBody.Velocity.x += objectBuffer[Idx].rigidBody.Force.x / objectBuffer[Idx].rigidBody.Mass * dt;
    objectBuffer[Idx].rigidBody.Velocity.y += objectBuffer[Idx].rigidBody.Force.y / objectBuffer[Idx].rigidBody.Mass * dt;
    objectBuffer[Idx].rigidBody.Velocity.z += objectBuffer[Idx].rigidBody.Force.z / objectBuffer[Idx].rigidBody.Mass * dt;

    objectBuffer[Idx].rigidBody.Force.x = 0;
    objectBuffer[Idx].rigidBody.Force.y = 0;
    objectBuffer[Idx].rigidBody.Force.z = 0;
}

void GPU::Update ()
{
    ObjectData *objectDatas = nullptr;
    cudaMallocHost(&objectDatas, Scene::World.EntityCount() * sizeof(ObjectData));
    unsigned int mSize = 0;

    for (Entity& entity : Scene::World.View<RigidBody>())
    {
        objectDatas[mSize].entityId = entity.GetId();

        if (!Scene::World.GetEntity(objectDatas[mSize].entityId).Active)
            continue;

        objectDatas[mSize].rigidBody = Scene::World.GetComponent<RigidBody>(objectDatas[mSize].entityId);

        if (objectDatas[mSize].hasTransform = Scene::World.HasComponent<Transform>(objectDatas[mSize].entityId))
        {
            objectDatas[mSize].transform = Scene::World.GetComponent<Transform>(objectDatas[mSize].entityId);
        }

        ++mSize;
    }

    ObjectData *objectBuffer = nullptr;
    cudaMalloc(&objectBuffer, Scene::World.EntityCount() * sizeof(ObjectData));
    cudaMemcpy(objectBuffer, objectDatas, Scene::World.EntityCount() * sizeof(ObjectData), cudaMemcpyHostToDevice);

    unsigned int threads = 256;
    unsigned int blocks = (mSize + threads - 1) / threads;
    Calculate<<<blocks, threads>>>(objectBuffer, Gravity, dt);

    cudaFreeHost(objectDatas);
}
