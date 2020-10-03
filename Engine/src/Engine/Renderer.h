#pragma once

#include "Camera.h"
#include "Components/Transform.h"
#include "Shader.h"
#include "SpriteSheet.h"
#include "Texture.h"

class Renderer 
{
  public:
    static void TexturedQuad(const Transform* trans, const Camera* cam, const Texture* texture);
    static void RenderSpriteSheet(const Transform* trans, const Camera* cam, const SpriteSheet* sheet, int x, int y);
  public:
    inline static bool m_QuadInitialized = false;
    inline static unsigned int m_QuadVBO;
    inline static unsigned int m_QuadVAO;
    inline static unsigned int m_QuadEBO;
    inline static float m_QuadVertices[] = {
       0.5f, 0.5f, 0.0f,      1.0f, 1.0f,
       0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
       -0.5f, 0.5f,  0.0f,    0.0f, 1.0f
    };
    inline static unsigned int m_QuadIndices[] = {0, 1, 3, 1, 2, 3};
    inline static Shader* m_TextureShader = nullptr;
};
