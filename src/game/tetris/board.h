#pragma once

#include "renderer.h"

class Board {
public:
  Board(int columns, int rows, float blockSize);

  void setOrigin(const glm::vec2& origin) {
    _origin = origin;
  }
  const glm::vec2& getOrigin() const {
    return _origin;
  }

  bool isBlockEmpty(int x, int y) const;
  void setBlock(int x, int y, BlockId blockId);

  void reset();
  void render(Renderer& renderer);

private:
  std::vector<uint32_t> _blocks;
  glm::vec2 _origin;
  float     _blockSize;
  uint32_t  _columns;
  uint32_t  _rows;
};
