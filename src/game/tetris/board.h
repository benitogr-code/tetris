#pragma once

#include "block_renderer.h"

class Board {
public:
  Board(int width, int height);

  void reset();
  void render(BlockRenderer& renderer);

private:
  std::vector<uint32_t> _blocks;
  glm::vec2 _position;
  uint32_t _width;
  uint32_t _height;
};
