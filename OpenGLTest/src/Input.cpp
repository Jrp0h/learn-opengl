#include "Input.h"
#include <GLFW/glfw3.h>

bool Input::IsKeyPressed(Key key) {
  if (m_Window == nullptr) {
    return false;
  }

  return glfwGetKey(m_Window, (int)key) == GLFW_PRESS;
}

void Input::SetWindow(GLFWwindow *window)
{
  m_Window = window;
}
