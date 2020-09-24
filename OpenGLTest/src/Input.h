#pragma once

#include <GLFW/glfw3.h>

enum class Key {
  A = GLFW_KEY_A,
  B = GLFW_KEY_B,
  C = GLFW_KEY_C,
  D = GLFW_KEY_D,
  E = GLFW_KEY_E,
  F = GLFW_KEY_F,
  G = GLFW_KEY_G,
  H = GLFW_KEY_H,
  I = GLFW_KEY_I,
  J = GLFW_KEY_J,
  K = GLFW_KEY_K,
  L = GLFW_KEY_L,
  M = GLFW_KEY_M,
  N = GLFW_KEY_N,
  O = GLFW_KEY_O,
  P = GLFW_KEY_P,
  Q = GLFW_KEY_Q,
  R = GLFW_KEY_R,
  S = GLFW_KEY_S,
  T = GLFW_KEY_T,
  U = GLFW_KEY_U,
  V = GLFW_KEY_V,
  W = GLFW_KEY_W,
  X = GLFW_KEY_X,
  Y = GLFW_KEY_Y,
  Z = GLFW_KEY_Z,
  UP = GLFW_KEY_UP,
  DOWN = GLFW_KEY_DOWN,
  LEFT = GLFW_KEY_LEFT,
  RIGHT = GLFW_KEY_RIGHT,
  LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
  RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
  SPACE = GLFW_KEY_SPACE,
  ESCAPE = GLFW_KEY_ESCAPE
};

class Input {
  public:
    static bool IsKeyPressed(Key key);

    static void SetWindow(GLFWwindow* window);

  private:
    inline static GLFWwindow* m_Window;
};

