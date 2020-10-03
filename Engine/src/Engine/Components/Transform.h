#pragma once

#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

class Transform {
  public:
    Transform(glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f))
      : m_Position(position), m_Rotation(rotation), m_Scale(scale) {}

  public:
    void SetPosition(glm::vec3 position) { m_Position = position; }
    void SetRotation(glm::vec3 rotation) {
      glm::vec3 newFront;
      newFront.x = cos(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));
      newFront.y = sin(glm::radians(rotation.y));
      newFront.z = sin(glm::radians(rotation.x)) * cos(glm::radians(rotation.y));

      m_Rotation = rotation;
      m_LocalFront = glm::normalize(newFront);
      m_LocalRight = glm::normalize(glm::cross(m_LocalFront, glm::vec3(0.0f, 1.0f, 0.0f)));
      m_LocalUp = glm::normalize(glm::cross(m_LocalRight, m_LocalFront));
    }
    void SetScale(glm::vec3 scale) { m_Scale = scale; }

    glm::vec3 GetPosition() const { return m_Position; }
    glm::vec3 GetRotation() const { return m_Rotation; }
    glm::vec3 GetScale() const { return m_Scale; }

    void Translate(glm::vec3 amount) { m_Position += amount; }
    void Rotate(glm::vec3 amount) { m_Rotation += amount; SetRotation(m_Rotation); }
    void Scale(glm::vec3 amount) { m_Scale += amount;  }


    inline glm::vec3 GetLocalFront() const { return m_LocalFront; }
    inline glm::vec3 GetLocalUp() const { return m_LocalUp; }
    inline glm::vec3 GetLocalRight() const { return m_LocalRight; };

    glm::mat4 GetMatrix() const {
      glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
      glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
      rotation = glm::rotate(rotation, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
      rotation = glm::rotate(rotation, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

      glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Scale);

      return transform * rotation * scale;
    }

  private:
    glm::vec3 m_Position;
    glm::vec3 m_Rotation;
    glm::vec3 m_Scale;

    glm::vec3 m_LocalUp = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_LocalFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 m_LocalRight = glm::vec3(0.0f, 1.0f, -1.0f);
};
