#pragma once

#include <string>

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Bind();

    void SetUniform4f(const char* name, float x, float y, float z, float w);
    void SetBool(const char* name, bool value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);

  private:
    void CompileShader(unsigned int type, const char* source);
    void CreateProgram();
    std::string ReadFromFile(const char* filepath);
  private:
    int m_Program;
    int m_VertexShader;
    int m_FragmentShader;

    // const char* m_VertexSource;
    // const char* m_FragmentSource;
};
