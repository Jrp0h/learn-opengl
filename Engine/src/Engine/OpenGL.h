#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <stdexcept>

class OpenGL {
public:
  static void Init()
  {
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable Debugging
    glDebugMessageCallback(OpenGL::DebugLogCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  }

  static void EnableDepthTest() { glEnable(GL_DEPTH_TEST); }
  static void DisableDepthTest() { glDisable(GL_DEPTH_TEST); }

  static void SetViewport(uint32_t width, uint32_t height) 
  {
    glViewport(0, 0, width, height);
  }

  static void Clear(glm::vec3 color)
  {
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  static void DebugLogCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParams)
  {
      switch(severity)
      {
          case GL_DEBUG_SEVERITY_HIGH:
            std::cerr << "[OpenGL Debug High] " << message << std::endl;
            throw std::runtime_error("[OpenGL Debug High]");
            break;
          case GL_DEBUG_SEVERITY_MEDIUM:
            std::cerr << "[OpenGL Debug Medium] " << message << std::endl;
            break;
          case GL_DEBUG_SEVERITY_LOW:
            std::cout << "[OpenGL Debug Low] " << message << std::endl;
            break;
          case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "[OpenGL Debug Notification] " << message << std::endl;
            break;
      }
  }
};

