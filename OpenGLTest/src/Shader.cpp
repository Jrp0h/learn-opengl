#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <exception>
#include <sstream>
#include <stdexcept>


Shader::Shader(const char* vertexSource, const char* fragmentSource)
  : m_VertexSource(vertexSource), m_FragmentSource(fragmentSource) {
    CompileVertex();
    CompileFragment();
    CreateProgram(); 
  }


void Shader::CompileVertex() {
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertexShader, 1, &m_VertexSource, nullptr);
    glCompileShader(m_VertexShader);

    int success;
    char infolog[512];
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &success);

    if(!success) 
    {
      glGetShaderInfoLog(m_VertexShader, 512, nullptr, infolog);
      std::stringstream ss;
      ss << "Shader:Vertex:Compilation " << infolog;
      throw std::runtime_error(ss.str().c_str());
    }
}

void Shader::CompileFragment() {

    unsigned int fragmentShader;
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragmentShader, 1, &m_FragmentSource, nullptr);
    glCompileShader(m_FragmentShader);

    int success;
    char infolog[512];
    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &success);

    if(!success) 
    {
      glGetShaderInfoLog(m_FragmentShader, 512, nullptr, infolog);
      std::stringstream ss;
      ss << "Shader:Fragment:Compilation " << infolog;
      throw std::runtime_error(ss.str().c_str());
    }
}


void Shader::CreateProgram() {
    m_Program = glCreateProgram();

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);

    glLinkProgram(m_Program);

    int success;
    char infolog[512];
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);

    if(!success) {
      glGetProgramInfoLog(m_Program, 512, nullptr, infolog);
      std::stringstream ss;
      ss << "Shader:Program:Link " << infolog;
      throw std::runtime_error(ss.str().c_str());
    }
}


void Shader::Bind() {
    glUseProgram(m_Program);
}


void Shader::SetUniform4f(const char *name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_Program, name), x, y, z, w);
}

void Shader::SetBool(const char *name, bool value)
{
    glUniform1l(glGetUniformLocation(m_Program, name), (int)value);
}
void Shader::SetInt(const char *name, int value)
{
    glUniform1l(glGetUniformLocation(m_Program, name), value);
}
void Shader::SetFloat(const char *name, float value)
{
    glUniform1f(glGetUniformLocation(m_Program, name), value);
}
