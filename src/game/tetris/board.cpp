#include "board.h"

const static uint32_t EMPTY_BLOCK = 0xFFFFFFFF;

Board::Board(int width, int height, float blockSize) {
  _blocks.resize(width*height, EMPTY_BLOCK);
  _blockSize = blockSize;
  _width = width;
  _height = height;
  _position = glm::vec2(0.0f);

  reset();
}

glm::vec2 Board::getBlockPosition(int x, int y) const {
  return _position + glm::vec2(x*_blockSize, y*_blockSize);
}

bool Board::isBlockEmpty(int x, int y) const {
  const auto idx = (y*_width) + x;

  return (idx < _blocks.size()) ? _blocks[idx] == EMPTY_BLOCK : true;
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
  for (int y = 0; y < _height; ++y) {
    for (int x = 0; x < _width; ++ x) {
      auto block = _blocks[(y*_width)+x];

      if (block != EMPTY_BLOCK) {
        const glm::vec2 blockPosition = _position + glm::vec2(x*_blockSize, y*_blockSize);
        renderer.drawBlock(blockPosition, (BlockId)block);
      }
    }
  }
}
