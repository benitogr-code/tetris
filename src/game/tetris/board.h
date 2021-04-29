#pragma once

#include "block_renderer.h"

class Board {
public:
  Board(int width, int height, float blockSize);

  glm::vec2 getBlockPosition(int x, int y) const;
  bool isBlockEmpty(int x, int y) const;

  void reset();
  void render(BlockRenderer& renderer);

private:
  std::vector<uint32_t> _blocks;
  glm::vec2 _position;
  float    _blockSize;
  uint32_t _width;
  uint32_t _height;
};
