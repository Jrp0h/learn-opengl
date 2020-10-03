#include "Shader.h"
#include <glm/glm.hpp>

#include <string>


class Light {
public:
  virtual void Use(Shader* shader){};

  inline void SetName(std::string name) { m_Name = name; }
  inline std::string GetName() const { return m_Name; }
protected:
  std::string m_Name;
  const char* calculateName(const char* member);
private:
  std::string temp;
};

class PointLight : public Light {
public:
  PointLight(std::string name) { m_Name = name; }
  void Use(Shader* shader) override;
public:
  inline void SetPosition(glm::vec3 position) { m_Position = position; }
  inline glm::vec3 GetPosition() const { return m_Position; }

  inline void SetDiffuse(glm::vec3 diffuse) { m_Diffuse = diffuse; }
  inline glm::vec3 GetDiffuse() const { return m_Diffuse; }

  inline void SetSpecular(glm::vec3 specular) { m_Specular = specular; }
  inline glm::vec3 GetSpecular() const { return m_Specular; }

  inline void SetAmbient(glm::vec3 ambient) { m_Ambient = ambient; }
  inline glm::vec3 GetAmbient() const { return m_Ambient; }

  inline void SetConstant(float constant) { m_Constant = constant; }
  inline float GetConstant() const { return m_Constant; }

  inline void SetLinear(float linear) { m_Linear = linear; }
  inline float GetLinear() const { return m_Linear; }

  inline void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }
  inline float GetQuadratic() const { return m_Quadratic; }
private:

  glm::vec3 m_Position;

  glm::vec3 m_Diffuse;
  glm::vec3 m_Specular;
  glm::vec3 m_Ambient;

  float m_Constant;
  float m_Linear;
  float m_Quadratic;
};

class DirectionalLight : public Light {
public:
  DirectionalLight(std::string name) { m_Name = name; }
  void Use(Shader* shader) override;
public:
  inline void SetDirection(glm::vec3 direction) { m_Direction = direction; }
  inline glm::vec3 GetDirection() const { return m_Direction; }

  inline void SetDiffuse(glm::vec3 diffuse) { m_Diffuse = diffuse; }
  inline glm::vec3 GetDiffuse() const { return m_Diffuse; }

  inline void SetSpecular(glm::vec3 specular) { m_Specular = specular; }
  inline glm::vec3 GetSpecular() const { return m_Specular; }

  inline void SetAmbient(glm::vec3 ambient) { m_Ambient = ambient; }
  inline glm::vec3 GetAmbient() const { return m_Ambient; }
private:
  glm::vec3 m_Direction;

  glm::vec3 m_Diffuse;
  glm::vec3 m_Specular;
  glm::vec3 m_Ambient;
};

class Spotlight : public Light {
public:
  Spotlight(std::string name) { m_Name = name; }
  void Use(Shader* shader) override;
public:
  inline void SetPosition(glm::vec3 position) { m_Position = position; }
  inline glm::vec3 GetPosition() const { return m_Position; }

  inline void SetDirection(glm::vec3 direction) { m_Direction = direction; }
  inline glm::vec3 GetDirection() const { return m_Direction; }

  inline void SetDiffuse(glm::vec3 diffuse) { m_Diffuse = diffuse; }
  inline glm::vec3 GetDiffuse() const { return m_Diffuse; }

  inline void SetSpecular(glm::vec3 specular) { m_Specular = specular; }
  inline glm::vec3 GetSpecular() const { return m_Specular; }

  inline void SetAmbient(glm::vec3 ambient) { m_Ambient = ambient; }
  inline glm::vec3 GetAmbient() const { return m_Ambient; }

  inline void SetCutOff(float cutOff) { m_CutOff = cutOff; }
  inline float GetCutOff() const { return m_CutOff; }

  inline void SetOuterCutOff(float outerCutOff) { m_OuterCutOff = outerCutOff; }
  inline float GetOuterCutOff() const { return m_OuterCutOff; }

  inline void SetLinear(float linear) { m_Linear = linear; }
  inline float GetLinear() const { return m_Linear; }

  inline void SetConstant(float constant) { m_Constant = constant; }
  inline float GetConstant() const { return m_Constant; }

  inline void SetQuadratic(float quadratic) { m_Quadratic = quadratic; }
  inline float GetQuadratic() const { return m_Quadratic; }

private:
  glm::vec3 m_Position;
  glm::vec3 m_Direction;

  glm::vec3 m_Diffuse;
  glm::vec3 m_Specular;
  glm::vec3 m_Ambient;

  float m_CutOff;
  float m_OuterCutOff;
  float m_Constant;
  float m_Linear;
  float m_Quadratic;
};
