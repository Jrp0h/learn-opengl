#include "Texture.h"

#include "vendor/stb_image/stb_image.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>
#include <exception>

Texture::Texture(const char* filePath)
  : m_Width(0), m_Height(0), m_FilePath(filePath)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int nrChannels;
    unsigned char* data = stbi_load(filePath, &m_Width, &m_Height, &nrChannels, 0);

    if(!data)
      throw std::runtime_error("Failed to load image");

    unsigned int type = nrChannels == 3 ? GL_RGB : GL_RGBA;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, type, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
