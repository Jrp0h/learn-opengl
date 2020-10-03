#include "Window.h"

#include <GLFW/glfw3.h>
#include <exception>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdexcept>

#include "Input.h"

Window::Window(uint32_t width, uint32_t height, const char* title)
  : m_Width(width), m_Height(height) 
{
    if(!glfwInit())
      throw std::runtime_error("Failed to initialize GLFW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_Window = glfwCreateWindow(m_Width, m_Height, title, nullptr, nullptr);

    if (m_Window == nullptr)
      throw std::runtime_error("Failed to create window");

    glfwMakeContextCurrent(m_Window);

    if (glewInit() != GLEW_OK)
      throw std::runtime_error("Failed to initialize GLEW\n");

    glfwSetWindowSizeCallback(m_Window, Window::OnResize);

    glViewport(0, 0, m_Width, m_Height);

    Input::SetWindow(m_Window);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(m_Window, Input::OnMouseMove);

    glfwSetWindowUserPointer(m_Window, (void*)this);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window()
{
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

bool Window::IsKeyPressed(int key) const
{
  return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

bool Window::ShouldClose() const
{
  return glfwWindowShouldClose(m_Window);
}

void Window::SetShouldClose(bool value)
{
  glfwSetWindowShouldClose(m_Window, value);
}

void Window::BeginFrame() const
{
  glClearColor(m_ClearColor.r, m_ClearColor.g, m_ClearColor.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::EndFrame() const {
  glfwSwapBuffers(m_Window);
  glfwPollEvents();
}

void Window::SetClearColor(float r, float g, float b)
{
  m_ClearColor.r = r;
  m_ClearColor.g = g;
  m_ClearColor.b = b;
}

void Window::SetClearColor(glm::vec3 color)
{
  m_ClearColor = color;
}

void Window::OnResize(GLFWwindow* window, int width, int height)
{
  auto t = (Window*)glfwGetWindowUserPointer(window);
  t->m_Width = width;
  t->m_Height = height;

  glViewport(0, 0, width, height);
}
