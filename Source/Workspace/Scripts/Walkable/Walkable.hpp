#pragma once
#include "Physics/Physics.hpp"
#include "Scene/Scene.hpp"
#include "Input/Input.hpp"

class Walkable
{
public:
    inline static void Update ()
    {
        for (Entity& entity : Scene::World.View<Transform, RigidBody, Walkable>())
        {
            Transform& transform = Scene::World.GetComponent<Transform>(entity.GetId());
            RigidBody& rigidBody = Scene::World.GetComponent<RigidBody>(entity.GetId());
            if (Input::GetKey(Input::Key_A) == Input::On_Press)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    -6,
                    0,
                    0
                ));
            }
            else if (Input::GetKey(Input::Key_D) == Input::On_Press)
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    6,
                    0,
                    0
                ));
            }
            else
            {
                rigidBody.SetVelocity(Arcarna::Math::Vector3(
                    0,
                    0,
                    0
                ));
            }
        }
    }
};