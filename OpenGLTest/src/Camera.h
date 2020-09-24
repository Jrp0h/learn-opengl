#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    Camera(float fov, unsigned int m_Width, unsigned int m_Height, float near = 0.1f, float far = 100.0f);

    void Translate(glm::vec3 position);
    void Rotate(float d, glm::vec3 rotation);

    inline glm::mat4 GetProjection() const { return m_Projection; }
    inline glm::mat4 GetTransform() const { return m_Transform; }
    inline float GetFOV() const { return m_Fov; }
    inline float GetAspectRatio() const { return m_AspectRation; }
    inline float GetNear() const { return m_AspectRation; }
    inline float GetFar() const { return m_AspectRation; }

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }
  private:
    glm::mat4 m_Projection;
    glm::mat4 m_Transform;
    float m_Fov;
    float m_AspectRation;
    float m_Near, m_Far;
    unsigned int m_Width, m_Height;
};
