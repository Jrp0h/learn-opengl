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

void Input::OnMouseMove(GLFWwindow *window, double xpos, double ypos)
{
    if(m_FirstMove)
    {
      m_LastX = xpos;
      m_LastY = ypos;
      m_FirstMove = false;
    }

    m_OffsetX = xpos - m_LastX;  
    m_OffsetY = ypos - m_LastY;  

    m_LastX = xpos;
    m_LastY = ypos;
}


float Input::GetMouseX() 
{
    float x = m_OffsetX;
    m_OffsetX = 0;
    return x;
}

float Input::GetMouseY() 
{
    float y = m_OffsetY;
    m_OffsetY = 0;
    return y;
}
