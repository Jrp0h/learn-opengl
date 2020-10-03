#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "SpriteSheet.h"

#include <GL/glew.h>
#include <GL/glew.h>
#include <iostream>

void Renderer::TexturedQuad(const Transform* trans, const Camera* cam, const Texture* texture)
{

    if(m_TextureShader == nullptr)
      m_TextureShader = new Shader("res/shaders/texture_vertex.glsl", "res/shaders/texture_fragment.glsl");

    float vertices[] = {
       0.5f, 0.5f, 0.0f,      1.0f, 1.0f,
       0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
       -0.5f, 0.5f,  0.0f,    0.0f, 1.0f
    };

    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    texture->Bind();

      m_TextureShader->SetMatrix4fv("u_Model", trans->GetMatrix());
      m_TextureShader->SetMatrix4fv("u_View", cam->GetView());
      m_TextureShader->SetMatrix4fv("u_Projection", cam->GetProjection());
      m_TextureShader->SetInt("u_Texture", 0);
      m_TextureShader->Bind();

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderSpriteSheet(const Transform *trans, const Camera *cam, const SpriteSheet *sheet, int x, int y)
{
    if(m_TextureShader == nullptr)
      m_TextureShader = new Shader("res/shaders/texture_vertex.glsl", "res/shaders/texture_fragment.glsl");

    float* coords = sheet->GetTextureCoordsFor(x, y);


    float vertices[] = {
       0.5f, 0.5f, 0.0f,      coords[0], coords[1],
       0.5f, -0.5f, 0.0f,    coords[2], coords[3],
       -0.5f, -0.5f, 0.0f,   coords[4], coords[5],
       -0.5f, 0.5f,  0.0f,    coords[6], coords[7]
    };

    unsigned int indices[] = {0, 1, 3, 1, 2, 3};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    sheet->Bind();

      m_TextureShader->SetMatrix4fv("u_Model", trans->GetMatrix());
      m_TextureShader->SetMatrix4fv("u_View", cam->GetView());
      m_TextureShader->SetMatrix4fv("u_Projection", cam->GetProjection());
      m_TextureShader->SetInt("u_Texture", 0);
      m_TextureShader->Bind();

      glBindVertexArray(VAO);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
