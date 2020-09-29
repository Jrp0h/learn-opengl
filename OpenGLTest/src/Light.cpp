#include "Light.h"
#include "Shader.h"
#include <sstream>
#include <iostream>

const char* Light::calculateName(const char* member) {
  std::stringstream ss;
  ss << m_Name << "." << member; 
  temp = std::move(ss.str());
  return temp.c_str();
}

void PointLight::Use(Shader* shader) {
  shader->SetVec3(calculateName("position"), m_Position);

  shader->SetVec3(calculateName("ambient"), m_Ambient);
  shader->SetVec3(calculateName("diffuse"), m_Diffuse);
  shader->SetVec3(calculateName("specular"), m_Specular);

  shader->SetFloat(calculateName("constant"), m_Constant);
  shader->SetFloat(calculateName("linear"), m_Linear);
  shader->SetFloat(calculateName("quadratic"), m_Quadratic);
}

void DirectionalLight::Use(Shader* shader) {
  shader->SetVec3(calculateName("direction"), m_Direction);

  shader->SetVec3(calculateName("ambient"), m_Ambient);
  shader->SetVec3(calculateName("diffuse"), m_Diffuse);
  shader->SetVec3(calculateName("specular"), m_Specular);
}

void Spotlight::Use(Shader* shader) {
  shader->SetVec3(calculateName("position"), m_Position); 
  shader->SetVec3(calculateName("direction"), m_Direction);

  shader->SetVec3(calculateName("ambient"), m_Ambient);
  shader->SetVec3(calculateName("diffuse"), m_Diffuse);
  shader->SetVec3(calculateName("specular"), m_Specular);

  shader->SetFloat(calculateName("constant"), m_Constant);
  shader->SetFloat(calculateName("linear"), m_Linear);
  shader->SetFloat(calculateName("quadratic"), m_Quadratic);

  shader->SetFloat(calculateName("cutOff"), m_CutOff);
  shader->SetFloat(calculateName("outerCutOff"), m_OuterCutOff);
}
