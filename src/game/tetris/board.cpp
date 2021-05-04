#include "board.h"

static constexpr uint32_t kEmptyBlock = 0xFFFFFFFF;

Board::Board(int columns, int rows, float blockSize) {
  _blocks.resize(columns*rows, kEmptyBlock);
  _origin = glm::vec2(0.0f);
  _blockSize = blockSize;
  _columns = columns;
  _rows = rows;

  reset();
}

bool Board::isBlockEmpty(int x, int y) const {
  const auto idx = (y*_columns) + x;

  return (idx < _blocks.size()) ? _blocks[idx] == kEmptyBlock : true;
}

void Board::setBlock(int x, int y, BlockId blockId) {
  const auto idx = (y*_columns) + x;

  if (idx < _blocks.size()) {
    _blocks[idx] = blockId;
  }
}


void Board::reset() {
  for (int idx = 0; idx < _blocks.size(); ++idx) {
    _blocks[idx] = kEmptyBlock;
  }

  for (int c = 0; c < _columns; ++c) {
    _blocks[c] = BlockId_Wall;
  }

  for (int r = 0; r < _rows; ++r) {
    _blocks[(r*_columns)] = BlockId_Wall;
    _blocks[((r+1)*_columns)-1] = BlockId_Wall;
  }
}

void Board::render(Renderer& renderer) {
  for (int r = 0; r < _rows; ++r) {
    for (int c = 0; c < _columns; ++ c) {
      auto block = _blocks[(r*_columns)+c];

      if (block != kEmptyBlock) {
        const glm::vec2 blockPosition = _origin + glm::vec2(c*_blockSize, r*_blockSize);
        renderer.drawBlock(blockPosition, (BlockId)block);
      }
    }
  }
}
