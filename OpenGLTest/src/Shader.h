#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
  public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    void Bind();
    void Unbind();

    void SetUniform4f(const char* name, float x, float y, float z, float w);
    void SetBool(const char* name, bool value);
    void SetInt(const char* name, int value);
    void SetFloat(const char* name, float value);

    void SetMatrix4fv(const char* name, glm::mat4 value);

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
