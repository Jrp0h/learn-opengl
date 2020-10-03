#pragma once

#include "Camera.h"
#include "Window.h"
#include <bits/stdint-uintn.h>
#include <glm/fwd.hpp>
#include <string>

class Application {
  public:
    Application(const char* title, uint32_t width, uint32_t height,  glm::vec3 clearColor)
    : m_Title(title), m_Width(width), m_Height(height), m_ClearColor(clearColor), m_CurrentCamera(nullptr) {}

  public:
    virtual void OnStart() {}
    virtual void OnUpdate() {}
    virtual void OnExit() {}

  public:
    const char* GetTitle() const { return m_Title; }
    const glm::vec3 GetClearColor() const { return m_ClearColor; }

    const uint32_t GetWidth() const { return m_Width; }
    const uint32_t GetHeight() const { return m_Height; }

    void SetWindow(Window* window) { m_Window = window; }


  protected:
    const char* m_Title;
    Window* m_Window;
    glm::vec3 m_ClearColor;

    Camera* m_CurrentCamera;

    uint32_t m_Width, m_Height;
};
