#pragma once

#include <string>

class Texture {
  public:
    Texture(const char* texturePath);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; } 
    inline int GetHeight() const { return m_Height; } 

    inline std::string GetType() const { return m_Type; } 
    inline void SetType(std::string type) { m_Type = type; } 
  private:
    unsigned int m_TextureID;
    std::string m_Type;
    int m_Width, m_Height;
    const char* m_FilePath;
};
