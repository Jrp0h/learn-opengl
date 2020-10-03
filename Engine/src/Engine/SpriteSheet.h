#pragma once

#include "Texture.h"

class SpriteSheet {
public:
  SpriteSheet(Texture* texture, unsigned int tileWidth, unsigned int tileHeight, unsigned int xCount, unsigned int yCount)
    : m_Texture(texture), m_TileWidth(tileWidth), m_TileHeight(tileHeight), m_CountX(xCount), m_CountY(yCount) {
    }

  
  float* GetTextureCoordsFor(unsigned int x, unsigned int y) const
  {
    float* coords = new float[2 * 4];

    y = m_CountY - y;

    coords[0] = (x * (float)m_TileWidth) / (float)m_Texture->GetWidth();
    coords[1] = (y * (float)m_TileHeight) / (float)m_Texture->GetHeight();

    coords[2] = ((x + 1) * (float)m_TileWidth) / (float)m_Texture->GetWidth();
    coords[3] = (y * (float)m_TileHeight) / (float)m_Texture->GetHeight();

    coords[4] = ((x + 1) * (float)m_TileWidth) / (float)m_Texture->GetWidth();
    coords[5] = ((y + 1) * (float)m_TileHeight) / (float)m_Texture->GetHeight();

    coords[6] = (x * (float)m_TileWidth) / (float)m_Texture->GetWidth();
    coords[7] = ((y + 1) * (float)m_TileHeight) / (float)m_Texture->GetHeight();

    return coords;
  }

  void Bind(unsigned int slot = 0) const {
    m_Texture->Bind(slot);
  }

private:
  Texture* m_Texture;
  unsigned int m_TileWidth, m_TileHeight;
  unsigned int m_CountX, m_CountY;
};
