#include "board.h"

const static uint32_t EMPTY_BLOCK = 0xFFFFFFFF;

Board::Board(int width, int height) {
  _blocks.resize(width*height, EMPTY_BLOCK);
  _width = width;
  _height = height;
  _position = glm::vec2(0.0f);

  reset();
}

void Board::reset() {
  for (int x = 0; x < _width; ++x) {
    _blocks[x] = BlockId_Wall;
  }

  for (int y = 0; y < _height; ++y) {
    _blocks[(y*_width)] = BlockId_Wall;
    _blocks[((y+1)*_width)-1] = BlockId_Wall;
  }
}

void Board::render(BlockRenderer& renderer) {
  const float size = renderer.getBlockSize();

  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++ x) {
      auto block = _blocks[(y*_width)+x];
      if (block != EMPTY_BLOCK) {
        const glm::vec2 blockPosition = _position + glm::vec2(x*size, y*size);
        renderer.drawBlock(blockPosition, (BlockId)block);
      }
    }
  }
}
