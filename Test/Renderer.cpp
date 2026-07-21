#include "Assert.hpp"
#include "Scene/Scene.hpp"
#include "Sprite/Sprite.hpp"
#include "Render/Renderer.hpp"
#include "Config.hpp"
#include "GLFW/glfw3.h"

int main ()
{
    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        1,
        1,
        "",
        nullptr,
        nullptr
    );

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    unsigned int SceneId = Scene::SetNewScene();
    unsigned int RectangleEId = Scene::World.NewEntity();
    unsigned int RectangleTId = Texture2D::Create("Assets/Images/Rectangle.png");
    Sprite Rectangle(RectangleTId);
    Scene::World.AddComponent<Renderer>(RectangleEId, Rectangle);
    Assert(0u, Scene::World.GetComponent<Renderer>(RectangleEId).Texture2DId, "Rectangle texture ID");

    unsigned int CircleEId = Scene::World.NewEntity();
    unsigned int CircleTId = Texture2D::Create("Assets/Images/Cicle.png");
    Sprite Circle(CircleTId);
    Scene::World.AddComponent<Renderer>(CircleEId, Circle);
    Assert(1u, Scene::World.GetComponent<Renderer>(CircleEId).Texture2DId, "Circle texture ID");
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}