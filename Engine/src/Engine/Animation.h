#pragma once

#include <glm/glm.hpp>

class Animation {
public:
  Animation(unsigned int startOffsetX, unsigned int startOffsetY, unsigned int endOffsetX, unsigned int endOffsetY, unsigned int spriteCountX, unsigned int spriteCountY)
    : m_StartOffsetX(startOffsetX), m_StartOffsetY(startOffsetY), m_EndOffsetX(endOffsetX), m_EndOffsetY(endOffsetY), m_SpriteCountX(spriteCountX), m_SpriteCountY(spriteCountY)
  {
      unsigned int frameCount = 0;
      if (m_StartOffsetY == m_EndOffsetY) {
        frameCount = m_EndOffsetX - (m_StartOffsetX);
      }
      else {
        frameCount = m_SpriteCountX - (m_StartOffsetX);
        frameCount += m_SpriteCountX - (m_SpriteCountX - m_EndOffsetX);

        for(int i = 0; i < m_EndOffsetY - m_StartOffsetY - 1; i++)
        {
          frameCount += m_SpriteCountX;
        }
      }

      m_FrameCount = frameCount;
    }

  glm::vec2 GetOffsetByFrame(int frame)
  {
    unsigned int offsetX, offsetY;
    offsetX = m_StartOffsetX;
    offsetY = m_StartOffsetY;

    frame = frame % m_FrameCount;

    // Go Through all frames
    for(int i = 0; i < frame; i++)
    {
      if(++offsetX > m_SpriteCountX - 1)
      {
        offsetX = 0;
        offsetY++;
      }
    }

    return glm::vec2(offsetX, offsetY);
  }

private: 
unsigned int m_StartOffsetX, m_StartOffsetY;
unsigned int m_EndOffsetX, m_EndOffsetY;
unsigned int m_SpriteCountX, m_SpriteCountY;
unsigned int m_FrameCount;
};
