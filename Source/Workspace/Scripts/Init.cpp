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

namespace Arcarna
{
    void Init ()
    {
        unsigned int SceneId = Scene::SetNewScene();

        unsigned int RectangleEId = Scene::World.NewEntity<Transform, RigidBody>();

        unsigned int RectangleTId = Texture2D::Create("Source/Workspace/Assets/Images/Rectangle.png");
        Texture2D::Load(RectangleTId);
        Sprite Rectangle(RectangleTId);
        Scene::World.AddComponent<Renderer>(RectangleEId, Rectangle);
    }
}