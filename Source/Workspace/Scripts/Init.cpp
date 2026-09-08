#include <iostream>

#include "init.hpp"

#include "Scene/Scene.hpp"
#include "Physics/Physics.hpp"
#include "Physics/Transform.hpp"
#include "Physics/RigidBody.hpp"
#include "Mesh/Mesh.hpp"
#include "Texture/Texture2D.hpp"
#include "Sprite/Sprite.hpp"
#include "Render/Renderer.hpp"
#include "Camera/Camera.hpp"

namespace Arcarna
{
    void Init ()
    {
        unsigned int SceneId = Scene::SetNewScene();

        unsigned int CameraEId = Scene::World.NewEntity<Transform, Camera>();
        Scene::MainCameraEntityId = CameraEId;

        unsigned int RectangleEId = Scene::World.NewEntity<Transform, RigidBody>();

        unsigned int RectangleTId = Texture2D::Create("Source/Workspace/Assets/Images/Rectangle.png");
        Texture2D::Load(RectangleTId);
        Sprite Rectangle(RectangleTId);
        Scene::World.AddComponent<Renderer>(RectangleEId, Rectangle);
        Scene::World.GetComponent<Transform>(RectangleEId).SetPosition(Arcarna::Math::Vector3(-5, 0, 0));
        Scene::World.GetComponent<RigidBody>(RectangleEId).SetVelocity(Arcarna::Math::Vector3(6, 6, 0));

        unsigned int Rectangle2EId = Scene::World.NewEntity<Transform, RigidBody>();
        Scene::World.AddComponent<Renderer>(Rectangle2EId, Rectangle);
        Scene::World.GetComponent<Transform>(Rectangle2EId).SetPosition(Arcarna::Math::Vector3(3, 5, 0));
    }
}