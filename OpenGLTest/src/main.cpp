#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>

#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"

class TriangleApplication {
public:
  TriangleApplication(uint32_t width, uint32_t height, const char *title)
    : m_Width(width), m_Height(height), m_Title(title), m_Camera(), m_Window(width, height, title) {  }

  void Run() {
    // initGLFW();
    // createWindow();
    mainLoop();
    // cleanup();
  }

private:
  // void initGLFW() {
    // glfwInit();
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  // }
  // void createWindow() {
    // m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    // if (m_Window == nullptr)
      // throw std::runtime_error("Failed to create window");

    // glfwMakeContextCurrent(m_Window);

    // if (glewInit() != GLEW_OK)
      // throw std::runtime_error("Failed to initialize GLEW\n");

    // glfwSetWindowSizeCallback(m_Window, OnResize);

    // glViewport(0, 0, m_Width, m_Height);
  // }

  // static void OnResize(GLFWwindow *window, int width, int height) {
    // glViewport(0, 0, width, height);
  // }

  void mainLoop() {

    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f};
    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s),
    // and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coords attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader shader("res/shaders/texture_vertex.glsl", "res/shaders/texture_fragment.glsl");
    shader.SetInt("u_Texture", 0);
    shader.Bind();

    Texture texture("res/textures/wall.jpg");

    m_Camera = new Camera(45.0f, m_Width, m_Height);


    // Light
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    Shader lightShader("res/shaders/lit_vertex.glsl", "res/shaders/lit_fragment.glsl");
    lightShader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
    lightShader.SetVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    // m_Transform = glm::translate(m_Transform, glm::vec3(0.1f, 0.0f, 0.0f));
    while (!m_Window.ShouldClose()) {

      float currentFrame = glfwGetTime();
      deltaTime = currentFrame - lastFrame;
      lastFrame = currentFrame;

      processInput(deltaTime);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      texture.Bind();
      shader.Bind();
      glBindVertexArray(VAO);

      for (int i = 0; i < 10; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(20.0f * i), glm::vec3(1.0f, 0.3f, 0.5f));

        shader.SetMatrix4fv("u_Model", model);
        shader.SetMatrix4fv("u_View", m_Camera->GetTransform());
        shader.SetMatrix4fv("u_Projection", m_Camera->GetProjection());
        glDrawArrays(GL_TRIANGLES, 0, 36);
      }

      m_Window.SwapBuffers();
      glfwPollEvents();
    }
  }

  void processInput(float dt) {
    if (Input::IsKeyPressed(Key::ESCAPE))
      m_Window.SetShouldClose(true);
    if (Input::IsKeyPressed(Key::D))
      m_Camera->Translate(glm::vec3(-1.0f * dt, 0.0f, 0.0f));
    if (Input::IsKeyPressed(Key::A))
      m_Camera->Translate(glm::vec3(1 * dt, 0.0f, 0.0f));
    if (Input::IsKeyPressed(Key::W))
      m_Camera->Translate(glm::vec3(0.0f, 0.0f, 1 * dt));
    if (Input::IsKeyPressed(Key::S))
      m_Camera->Translate(glm::vec3(0.0f, 0.0f, -1 * dt));
    if (Input::IsKeyPressed(Key::SPACE))
      m_Camera->Translate(glm::vec3(0.0f, -1 * dt, 0.0f));
    if (Input::IsKeyPressed(Key::LEFT_SHIFT))
      m_Camera->Translate(glm::vec3(0.0f, 1 * dt, 0.0f));

    if (Input::IsKeyPressed(Key::DOWN))
      m_Camera->Rotate(-10 * dt, glm::vec3(1, 0.0f, 0.0f));
    if (Input::IsKeyPressed(Key::UP))
      m_Camera->Rotate(10 * dt, glm::vec3(1, 0.0f, 0.0f));
    if (Input::IsKeyPressed(Key::LEFT))
      m_Camera->Rotate(10 * dt, glm::vec3(0.0f, 1.0f, 0.0f));
    if (Input::IsKeyPressed(Key::RIGHT))
      m_Camera->Rotate(-10 * dt, glm::vec3(0.0f, 1, 0.0f));
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
  TriangleApplication app(800, 600, "OpenGl Window");
  try {
    app.Run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
