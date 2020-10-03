#include <cstring>
#include <iostream>

#include <Engine/Engine.h>
#include <Engine/Renderer.h>
#include <Engine/Application.h>
#include <Engine/Camera.h>
#include <Engine/Components/Transform.h>

class TestApplication : public Application {
public:
   TestApplication(const char* title, uint32_t width, uint32_t height,  glm::vec3 clearColor): Application(title, width, height, clearColor) {

      m_Camera = new Camera(45.0f, m_Width, m_Height);
      m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));
      m_Camera->SetRotation(glm::vec3(90.0f, 0.0f, 0.0f));

      m_PlayerTransform.SetRotation(glm::vec3(0.0f, 00.0f, -90.0f));

      m_SpriteSheet = new Texture("res/textures/spritesheet.png");
      m_Face = new Texture("res/textures/awesomeface.png", true);

      m_Sheet = new SpriteSheet(m_SpriteSheet, 64, 44, 6, 9);
      m_Idle = new Animation(1, 1, 6, 1, 6, 9);
      m_Run = new Animation(1, 2, 2, 3, 6, 9);

      m_Animator->AddAnimation("idle", m_Idle);
      m_Animator->AddAnimation("run", m_Run);
   }
public:
   
    void OnUpdate() override {
      ProccessInput();

      m_Animator->UpdateTime();

      glm::vec2 currImg = m_Animator->GetCurrentOffset();
      Renderer::RenderSpriteSheet(&m_PlayerTransform, m_Camera, m_Sheet, currImg.x, currImg.y);
    }

    void ProccessInput()
    {
       float dt = Time::GetDeltaTime();
       auto currentPos = m_PlayerTransform.GetPosition();
       float playerSpeed = 5.0f;

       if (Input::IsKeyPressed(Key::ESCAPE))
         m_Window->SetShouldClose(true);
       
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
         m_Animator->StartAnimation("idle");
       else 
         m_Animator->StartAnimation("run");
    }

private:
   Transform m_Transform;
   Camera* m_Camera;

   Texture* m_Face;

   Transform m_PlayerTransform;
   Texture* m_SpriteSheet;
   SpriteSheet* m_Sheet;

   Animator* m_Animator;

   Animation* m_Idle;
   Animation* m_Run;
};

int main()
{
  try {
   TestApplication app("Test", 800, 600, {0.2f, 0.3f, 0.3f});

   Engine e(app);
   e.Run();

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
