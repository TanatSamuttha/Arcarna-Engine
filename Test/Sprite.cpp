#include "Assert.hpp"
#include "Scene/Scene.hpp"
#include "Sprite/Sprite.hpp"
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

    unsigned int entityId = Scene::World.NewEntity();

    Scene::World.AddComponent<Sprite>(entityId, "Assets/Images/Rectangle.png");

    Assert(0u, Scene::World.GetComponent<Sprite>(entityId).SpriteTexture.GetTextureId(), "Before load texture");
    
    Scene::World.GetComponent<Sprite>(entityId).SpriteTexture.Load();

    Assert(true, (bool)Scene::World.GetComponent<Sprite>(entityId).SpriteTexture.GetTextureId(), "After load texture");

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}