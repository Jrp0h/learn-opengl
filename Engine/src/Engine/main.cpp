#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <glm/fwd.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Camera.h"
#include "Components/Transform.h"
#include "Input.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Light.h"
#include "Time.h"
#include "Model.h"
#include "SpriteSheet.h"
#include "Animation.h"
#include "Animator.h"

class TriangleApplication {
public:
  TriangleApplication(uint32_t width, uint32_t height, const char *title)
    : m_Width(width), m_Height(height), m_Title(title), m_Camera(), m_Window(width, height, title), m_Animator(0.125f)  {  }

  void Run() {
    mainLoop();
  }

private:
  void mainLoop() {

    m_Window.SetClearColor(0.2f, 0.3f, 0.3f);

    m_Camera = new Camera(45.0f, m_Width, m_Height);
    m_Camera->SetPosition(glm::vec3(0.0f, 0, -3.0f));
    m_Camera->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));


    // Shader shader("res/shaders/texture_vertex.glsl", "res/shaders/texture_fragment.glsl");
    Texture texture("res/textures/spritesheet.png");
    Texture texture2("res/textures/awesomeface.png", true);

    SpriteSheet sheet(&texture, 64, 44, 6, 9);

    Animation idle(1, 1, 6, 1, 6, 9);
    Animation run(1, 2, 2, 3, 6, 9);

    m_Animator.AddAnimation("idle", &idle);
    m_Animator.AddAnimation("run", &run);

    m_PlayerTransform.SetRotation(glm::vec3(0.0f, 00.0f, -90.0f));


    while (!m_Window.ShouldClose()) {
      Time::UpdateDeltaTime();

      // std::cout << "FPS: " << 1.0f / Time::GetDeltaTime() << std::endl;

      m_Window.BeginFrame();
      m_Animator.UpdateTime();

      processInput(Time::GetDeltaTime());

      glm::vec2 currImg = m_Animator.GetCurrentOffset();

      // Renderer::TexturedQuad(&m_PlayerTransform, m_Camera, &texture2);
      Renderer::RenderSpriteSheet(&m_PlayerTransform, m_Camera, &sheet, currImg.x, currImg.y);
      // Renderer::TexturedQuad(&m_PlayerTransform, m_Camera, &texture2);
      // Renderer::TexturedQuad(&m_PlayerTransform, m_Camera, &texture);

      m_Window.EndFrame();
    }
  }

  void processInput(float dt) {
   
    auto currentPos = m_PlayerTransform.GetPosition();
    float playerSpeed = 5.0f;

    if (Input::IsKeyPressed(Key::ESCAPE))
      m_Window.SetShouldClose(true);
    
    if (Input::IsKeyPressed(Key::D))
    {
      currentPos += (playerSpeed * dt);
      m_PlayerTransform.SetScale(glm::vec3(1.0f, 1.0f, 1.0f));
    }
    if (Input::IsKeyPressed(Key::A))
    {
      currentPos -= (playerSpeed * dt);
      m_PlayerTransform.SetScale(glm::vec3(1.0f, -1.0f, 1.0f));
    }

    if(currentPos == m_PlayerTransform.GetPosition())
      m_Animator.StartAnimation("idle");
    else 
      m_Animator.StartAnimation("run");
  
  }

private:
  uint32_t m_Width, m_Height;
  const char *m_Title;

  Window m_Window;
  Camera* m_Camera;

  const char *m_VertexShader;
  const char *m_FragmentShader;

  float deltaTime, lastFrame;

  Animator m_Animator;
  Transform m_PlayerTransform;
};

int main() {
  try {
    TriangleApplication app(800, 600, "OpenGl Window");
    app.Run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
