#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
  CompileShader(GL_VERTEX_SHADER, ReadFromFile(vertexPath).c_str());
  CompileShader(GL_FRAGMENT_SHADER, ReadFromFile(fragmentPath).c_str());
  CreateProgram();
}

Shader::~Shader()
{
  glDeleteShader(m_Program);
}

std::string Shader::ReadFromFile(const char* filepath) {
  std::ifstream file; 

  file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  file.open(filepath);

  if(file.fail())
  {
    std::stringstream ss;
    ss << "Failed to open " << filepath; 
    throw std::runtime_error(ss.str().c_str());
  }

  std::stringstream content;

  content << file.rdbuf();  

  file.close();

  return content.str();
}

void Shader::CompileShader(unsigned int type, const char* source) {
  int shader = glCreateShader(type);

  if(type == GL_VERTEX_SHADER) m_VertexShader = shader;
  else if(type == GL_FRAGMENT_SHADER) m_FragmentShader = shader;
  else throw std::runtime_error("Invalid shader type");
  
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  char infolog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, nullptr, infolog);
    std::stringstream ss;
    ss << "Shader:" << (type == GL_FRAGMENT_SHADER ? "Fragment" : "Vertex") << ":Compilation " << infolog;
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

  if (!success) {
    glGetProgramInfoLog(m_Program, 512, nullptr, infolog);
    std::stringstream ss;
    ss << "Shader:Program:Link " << infolog;
    throw std::runtime_error(ss.str().c_str());
  }
}

void Shader::Bind() { glUseProgram(m_Program); }
void Shader::Unbind() {
  glUseProgram(0);
}
void Shader::SetUniform4f(const char *name, float x, float y, float z, float w) {
  glUniform4f(glGetUniformLocation(m_Program, name), x, y, z, w);
}

void Shader::SetBool(const char *name, bool value) {
  glUniform1i(glGetUniformLocation(m_Program, name), (int)value);
}
void Shader::SetInt(const char *name, int value) {
  glUniform1i(glGetUniformLocation(m_Program, name), value);
}
void Shader::SetFloat(const char *name, float value) {
  glUniform1f(glGetUniformLocation(m_Program, name), value);
}

void Shader::SetMatrix4fv(const char *name, glm::mat4 value)
{
  glUniformMatrix4fv(glGetUniformLocation(m_Program, name), 1, GL_FALSE, glm::value_ptr(value));
}
