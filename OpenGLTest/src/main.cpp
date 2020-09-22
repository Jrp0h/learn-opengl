#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <math.h>

class TriangleApplication {
public:
  TriangleApplication(uint32_t width, uint32_t height, const char *title)
    : m_Width(width), m_Height(height), m_Title(title) {
  }

  void Run() {
    initGLFW();
    createWindow();
    mainLoop();
    cleanup();
  }

private:
  void initGLFW() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
  }
  void createWindow() {
    m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    if (m_Window == nullptr) 
      throw std::runtime_error("Failed to create window");
    

    glfwMakeContextCurrent(m_Window);
    
    if (glewInit() != GLEW_OK)
        throw std::runtime_error("Failed to initialize GLEW\n");

    glViewport(0, 0, m_Width, m_Height);
  }
  void mainLoop() {

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f,  -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        0.0f,   0.5f, 0.0f,     0.0f, 1.0f, 1.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    Shader shader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    shader.Bind();

    while (!glfwWindowShouldClose(m_Window)) {

      processInput();

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      
      // double time = glfwGetTime();
      // double greenValue = (time / 1.0f) + 0.5f;

      // shader.SetUniform4f("outColor", 1.0f, greenValue, 1.0f, 1.0f);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(m_Window);
      glfwPollEvents();
    }
  }
  void cleanup() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
  }

  void processInput() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(m_Window, true);
    }
  }

private:
  uint32_t m_Width, m_Height;
  const char *m_Title;
  GLFWwindow *m_Window;

  const char* m_VertexShader;
  const char* m_FragmentShader;
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
