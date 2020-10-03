#pragma once

#include "Animation.h"
#include "Time.h"
#include "Utils.h"
#include <glm/fwd.hpp>
#include <map>
#include <stdexcept>

class Animator {
  public:
    Animator(float spacing): m_Spacing(spacing) {}

    void AddAnimation(const char* name, Animation* animation)
    {
      m_Animations.insert(std::make_pair(name, animation));
    }

    void UpdateTime() {
      m_T += Time::GetDeltaTime();

      if(m_T > m_Spacing)
      {
        m_CurrentFrame++;
        m_T = 0;
      }
    }

    glm::vec2 GetCurrentOffset()
    {
      if(m_CurrentAnimation == nullptr)
        return glm::vec2();

      return m_CurrentAnimation->GetOffsetByFrame(m_CurrentFrame);
    }

    void StartAnimation(const char* name)
    {
      if(m_CurrentAnimation == m_Animations[name])
        return;

      m_CurrentAnimation = m_Animations[name];
      m_CurrentFrame = 0;
    }
  private:
    float m_T;
    float m_Spacing;
    unsigned int m_CurrentFrame;
    std::map<const char*, Animation*> m_Animations;
    Animation* m_CurrentAnimation;
};
