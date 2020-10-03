#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window {
public:
  Window(uint32_t width, uint32_t height, const char* title);
  ~Window();

  inline uint32_t GetWidth() const { return m_Width; }
  inline uint32_t GetHeight() const { return m_Height; }

  bool IsKeyPressed(int key) const;

  bool ShouldClose() const;
  void SetShouldClose(bool value);
  void BeginFrame() const;
  void EndFrame() const;
  void SetClearColor(float r, float g, float b);
  void SetClearColor(glm::vec3 color);

  void SwapBuffers() const;

private:
  static void OnResize(GLFWwindow * window, int width, int height);

private:
  GLFWwindow* m_Window;
  uint32_t m_Width, m_Height;
  char* m_Title;
  glm::vec3 m_ClearColor;
};
