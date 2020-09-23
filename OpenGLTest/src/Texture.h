#pragma once

class Texture {
  public:
    Texture(const char* texturePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; } 
    inline int GetHeight() const { return m_Height; } 
  private:
    unsigned int m_TextureID;
    int m_Width, m_Height;
    const char* m_FilePath;
};
