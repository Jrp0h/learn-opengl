#pragma once 

#include <GLFW/glfw3.h>

class Time {
  public:
    static double GetDeltaTime() { return m_DeltaTime; }

    static void UpdateDeltaTime() {
      float currentFrame = glfwGetTime();
      m_DeltaTime = currentFrame - m_LastFrame;
      m_LastFrame = currentFrame;
    }

  private:
    inline static double m_DeltaTime;
    inline static double m_LastFrame;
};
