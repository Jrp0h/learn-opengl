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
#include "Input.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "Light.h"

class TriangleApplication {
public:
  TriangleApplication(uint32_t width, uint32_t height, const char *title)
    : m_Width(width), m_Height(height), m_Title(title), m_Camera(), m_Window(width, height, title) {  }

  void Run() {
    mainLoop();
  }

private:
  void mainLoop() {

    glEnable(GL_DEPTH_TEST);

  
float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };


    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    unsigned int VBO, VAO; //, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    m_Camera = new Camera(45.0f, m_Width, m_Height);
    m_Camera->SetPosition(glm::vec3(0.0f, 0, 5));

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glm::vec3 cubePositions[] = { 
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, -1.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f), 
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

    glm::vec3 pointLights[] = { 
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    Shader litShader("res/shaders/lit_vertex.glsl", "res/shaders/lit_fragment.glsl");
    Texture box("res/textures/container2.png");
    Texture boxSpecular("res/textures/container2_specular.png");

    while (!m_Window.ShouldClose()) {
      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(deltaTime);

      glClearColor(0.3f, 0.2f, 0.2f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      for(int i = 0; i < 10; i++)
      {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

        litShader.Bind();
        
        litShader.SetInt("u_Material.diffuse", 0);
        box.Bind();

        litShader.SetInt("u_Material.specular", 1);
        boxSpecular.Bind(1);

        litShader.SetFloat("u_Material.shininess", 32.0f);

        // Point Light
        PointLight pointLight("");

        for(int i = 0; i < sizeof(pointLights)/sizeof(pointLights[0]); i++)
        {
          pointLight.SetName("u_PointLights[" + std::to_string(i) + "]");
          pointLight.SetPosition(pointLights[i]);

          pointLight.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
          pointLight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
          pointLight.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

          pointLight.SetConstant(1.0f);
          pointLight.SetLinear(0.09f);
          pointLight.SetQuadratic(0.032f);
          pointLight.Use(&litShader);
        }

        // Directional Light
        DirectionalLight directionalLight("u_DirectionLight");
        directionalLight.SetDirection(glm::vec3(-0.2f, -1.0f, 0.3f));

        directionalLight.SetDiffuse(glm::vec3(0.2f, 0.2f, 0.2f));
        directionalLight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
        directionalLight.SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));

        directionalLight.Use(&litShader);

        // Spotlight
        Spotlight spotlight("u_Spotlight");
        spotlight.SetPosition(m_Camera->GetPosition());
        spotlight.SetDirection(m_Camera->GetFront());
        spotlight.SetCutOff(glm::cos(glm::radians(12.5f)));
        spotlight.SetOuterCutOff(glm::cos(glm::radians(17.5f)));

        spotlight.SetDiffuse(glm::vec3(0.5f, 0.5f, 0.5f));
        spotlight.SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
        spotlight.SetSpecular(glm::vec3(1.0f, 1.0f, 1.0f));

        spotlight.SetConstant(1.0f);
        spotlight.SetLinear(0.09f);
        spotlight.SetQuadratic(0.032f);

        spotlight.Use(&litShader);
        litShader.SetMatrix4fv("u_Model", model);
        litShader.SetMatrix4fv("u_View", m_Camera->GetView());
        litShader.SetMatrix4fv("u_Projection", m_Camera->GetProjection());
        litShader.SetVec3("u_ViewPosition", m_Camera->GetPosition());

        litShader.Bind();
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);
      }

      m_Window.SwapBuffers();
      glfwPollEvents();
    }
  }

  void processInput(float dt) {
    
    float sensitivity = 0.05f;
    glm::vec3 rotation = m_Camera->GetRotation();
    rotation.x += Input::GetMouseX() * sensitivity;
    rotation.y -= Input::GetMouseY() * sensitivity;

    if(rotation.y > 89.0f)
      rotation.y = 89.0f;
    if(rotation.y < -89.0f)
      rotation.y = -89.0f;

    m_Camera->SetRotation(rotation);

    auto currentPos = m_Camera->GetPosition();
    float cameraSpeed = 5.0f;
  
    if(Input::IsKeyPressed(Key::LEFT_CONTROL))
      cameraSpeed = 1.0f;

    if (Input::IsKeyPressed(Key::ESCAPE))
      m_Window.SetShouldClose(true);
    if (Input::IsKeyPressed(Key::D))
      currentPos += (cameraSpeed * dt * m_Camera->GetRight());
    if (Input::IsKeyPressed(Key::A))
      currentPos -= (cameraSpeed * dt * m_Camera->GetRight());
    if (Input::IsKeyPressed(Key::W))
      currentPos += (cameraSpeed * dt * m_Camera->GetFront());
    if (Input::IsKeyPressed(Key::S))
      currentPos -= (cameraSpeed * dt * m_Camera->GetFront());
    if (Input::IsKeyPressed(Key::SPACE))
      currentPos -= (cameraSpeed * dt * glm::vec3(0.0f, -1.0f, 0.0f));
    if (Input::IsKeyPressed(Key::LEFT_SHIFT))
      currentPos -= (cameraSpeed * dt * glm::vec3(0.0f, 1.0f, 0.0f));

    m_Camera->SetPosition(currentPos);
  }

private:
  uint32_t m_Width, m_Height;
  const char *m_Title;

  Window m_Window;
  Camera* m_Camera;

  const char *m_VertexShader;
  const char *m_FragmentShader;

  float deltaTime, lastFrame;
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
