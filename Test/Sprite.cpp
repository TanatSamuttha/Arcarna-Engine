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
    unsigned int TextureId = Texture2D::Create("Assets/Images/Rectangle.png");

    Scene::World.AddComponent<Sprite>(entityId, TextureId);

    Sprite& SpriteComponent = Scene::World.GetComponent<Sprite>(entityId);
    Assert(0u, Texture2D::GetTextureId(SpriteComponent.SpriteTextureId), "Before load texture");
    
    Texture2D::Load(SpriteComponent.SpriteTextureId);
    Assert(true, (bool)Texture2D::GetTextureId(SpriteComponent.SpriteTextureId), "After load texture");

    Texture2D::Unload(TextureId);
    Assert(0u, Texture2D::GetTextureId(SpriteComponent.SpriteTextureId), "Unload texture");

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}