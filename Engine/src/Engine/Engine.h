#pragma once

#include "Window.h"
#include "Application.h"
#include "Input.h"
#include "Light.h"
#include "Shader.h"
#include "Texture.h"
#include "Time.h"
#include "Utils.h"
#include "Vertex.h"
#include "Components/Transform.h"
#include "Animation.h"
#include "Animator.h"
#include "Camera.h"
#include "Renderer.h"
#include "SpriteSheet.h"

class Engine {
public:
    Engine(Application& app);

    void Run();
private:
    Window* m_Window;
    Application* m_App;
};
