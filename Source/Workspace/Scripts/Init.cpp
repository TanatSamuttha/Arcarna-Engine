#include "Init.hpp"

#include "ECS/System.hpp"
#include "Scene/Scene.hpp"
#include "Physics/Transform.hpp"
#include "Physics/RigidBody.hpp"
#include "Render/Renderer.hpp"
#include "Camera/Camera.hpp"

#include "BoundChecker/HorizontalBound.hpp"
#include "BoundChecker/VerticalBound.hpp"
#include "AddBoxes/AddBoxes.hpp"

namespace Arcarna
{
    void Init ()
    {
        unsigned int SceneId = Scene::SetNewScene();

        unsigned int CameraEId = Scene::World.NewEntity<Transform, Camera>();
        Scene::MainCameraEntityId = CameraEId;

        AddBoxes::RectangleTId = Texture2D::Create("Source/Workspace/Assets/Images/Rectangle.png");
        Texture2D::Load(AddBoxes::RectangleTId);

        AddBoxes::Start();
        System::AddUpdate(Horizontalbound::Update, "Hori");
        System::AddUpdate(Verticalbound::Update, "Verti");
    }
}