#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

Camera::Camera(float fov, unsigned int width, unsigned int height, float near, float far)
    : m_Fov(fov), m_Width(width), m_Height(height), m_Near(near), m_Far(far), m_AspectRation((float)width / (float)height)
{
  m_Projection = glm::perspective(glm::radians(fov), (float)width / (float)height, near, far);
  m_Transform = glm::mat4(1.0f);
}

void Camera::Translate(glm::vec3 position) 
{
  m_Transform = glm::translate(m_Transform, position);
}

void Camera::Rotate(float d, glm::vec3 rotation)
{
    m_Transform = glm::rotate(m_Transform, glm::radians(d), rotation);
}
