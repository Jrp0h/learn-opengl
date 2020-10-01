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
  ZERO = GLFW_KEY_0,
  ONE = GLFW_KEY_1,
  TWO = GLFW_KEY_2,
  THREE = GLFW_KEY_3,
  FOUR = GLFW_KEY_4,
  FIVE = GLFW_KEY_5,
  SIX = GLFW_KEY_6,
  SEVEN = GLFW_KEY_7,
  EIGHT = GLFW_KEY_8,
  NINE = GLFW_KEY_9,
  KP_ZERO = GLFW_KEY_KP_0,
  KP_ONE = GLFW_KEY_KP_1,
  KP_TWO = GLFW_KEY_KP_2,
  KP_THREE = GLFW_KEY_KP_3,
  KP_FOUR = GLFW_KEY_KP_4,
  KP_FIVE = GLFW_KEY_KP_5,
  KP_SIX = GLFW_KEY_KP_6,
  KP_SEVEN = GLFW_KEY_KP_7,
  KP_EIGHT = GLFW_KEY_KP_8,
  KP_NINE = GLFW_KEY_KP_9,
  ENTER = GLFW_KEY_ENTER,
  KP_ENTER = GLFW_KEY_KP_ENTER,
  UP = GLFW_KEY_UP,
  DOWN = GLFW_KEY_DOWN,
  LEFT = GLFW_KEY_LEFT,
  RIGHT = GLFW_KEY_RIGHT,
  LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
  RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
  SPACE = GLFW_KEY_SPACE,
  ESCAPE = GLFW_KEY_ESCAPE,
  LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL
};

class Input {
  public:
    static bool IsKeyPressed(Key key);

    static float GetMouseY();
    static float GetMouseX();

    static void SetWindow(GLFWwindow* window);
    static void OnMouseMove(GLFWwindow* window, double xpos, double ypos);

  private:
    inline static GLFWwindow* m_Window;
    inline static double m_LastX = 0, m_LastY = 0;
    inline static float m_OffsetX = 0, m_OffsetY = 0;
    inline static bool m_FirstMove = true;

};

