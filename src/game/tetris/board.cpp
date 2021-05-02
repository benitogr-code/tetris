#include "board.h"

const static uint32_t EMPTY_BLOCK = 0xFFFFFFFF;

Board::Board(int columns, int rows, float blockSize) {
  _blocks.resize(columns*rows, EMPTY_BLOCK);
  _origin = glm::vec2(0.0f);
  _blockSize = blockSize;
  _columns = columns;
  _rows = rows;

  reset();
}

bool Board::isBlockEmpty(int x, int y) const {
  const auto idx = (y*_columns) + x;

  return (idx < _blocks.size()) ? _blocks[idx] == EMPTY_BLOCK : true;
}

void Board::reset() {
  for (int c = 0; c < _columns; ++c) {
    _blocks[c] = BlockId_Wall;
  }

  for (int r = 0; r < _rows; ++r) {
    _blocks[(r*_columns)] = BlockId_Wall;
    _blocks[((r+1)*_columns)-1] = BlockId_Wall;
  }
}

void Board::render(BlockRenderer& renderer) {
  for (int r = 0; r < _rows; ++r) {
    for (int c = 0; c < _columns; ++ c) {
      auto block = _blocks[(r*_columns)+c];

      if (block != EMPTY_BLOCK) {
        const glm::vec2 blockPosition = _origin + glm::vec2(c*_blockSize, r*_blockSize);
        renderer.drawBlock(blockPosition, (BlockId)block);
      }
    }
  }
}
