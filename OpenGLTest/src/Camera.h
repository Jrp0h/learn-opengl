#pragma once

#include <glm/glm.hpp>

class Camera {
  public:
    Camera(float fov, unsigned int m_Width, unsigned int m_Height, float near = 0.1f, float far = 100.0f);

    void Translate(glm::vec3 position);
    void Rotate(float d, glm::vec3 rotation);

    inline glm::mat4 GetProjection() const { return m_Projection; }
    glm::mat4 GetView() const;
    inline float GetFOV() const { return m_Fov; }
    inline float GetAspectRatio() const { return m_AspectRation; }
    inline float GetNear() const { return m_AspectRation; }
    inline float GetFar() const { return m_AspectRation; }

    inline glm::vec3 GetFront() const { return glm::vec3(0.0f, 0.0f, -1.0f); }
    inline glm::vec3 GetUp() const { return m_Up; }
    inline glm::vec3 GetLeft() const { return glm::normalize(glm::cross(GetFront(), GetUp())); };

    inline glm::vec3 GetPosition() const { return m_Position; }
    inline glm::vec3 GetRotation() const { return m_Rotation; }

    inline void SetPosition(glm::vec3 position) { m_Position = position; }
    void SetRotation(glm::vec3 rotation);

    inline unsigned int GetWidth() const { return m_Width; }
    inline unsigned int GetHeight() const { return m_Height; }


  private:
    glm::mat4 m_Projection;
    glm::mat4 m_Transform;
    float m_Fov;
    float m_AspectRation;
    float m_Near, m_Far;
    unsigned int m_Width, m_Height;

    glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 m_Position, m_Rotation;
};
