#include "board.h"

static constexpr uint32_t kEmptyBlock = 0xFFFFFFFF;

Board::Board(int columns, int rows, float blockSize) {
  _blocks.resize(columns*rows, kEmptyBlock);
  _fullRows.resize(rows, 0);
  _origin = glm::vec2(0.0f);
  _blockSize = blockSize;
  _columns = columns;
  _rows = rows;

  reset();
}

bool Board::hasFullRows() const {
  bool result = false;

  for (auto value: _fullRows) {
    result |= (value != 0);
  }

  return result;
};

uint32_t Board::clearFullRows() {
  std::vector<uint32_t> blocks;
  blocks.resize(_rows*_columns, kEmptyBlock);

  for (int c = 0; c < _columns; ++c) {
    blocks[c] = BlockId_Wall;
  }

  int targetRow = 1;
  for (int r = 1; r < _rows; ++r) {
    blocks[(r*_columns)] = BlockId_Wall;
    blocks[((r+1)*_columns)-1] = BlockId_Wall;

    if (_fullRows[r] != 0)
      continue;

    for (int c = 1; c < _columns-1; ++c) {
      const int targetIdx = (targetRow*_columns)+c;
      const int sourceIdx = (r*_columns)+c;
      blocks[targetIdx] = _blocks[sourceIdx];
    }
    targetRow++;
  }

  _blocks.swap(blocks);
  _fullRows.assign(_rows, 0);

  return _rows - targetRow;
}

bool Board::isBlockEmpty(int x, int y) const {
  const auto idx = (y*_columns) + x;

  return (idx < _blocks.size()) ? _blocks[idx] == kEmptyBlock : true;
}

void Board::setBlock(int x, int y, BlockId blockId) {
  const auto idx = (y*_columns) + x;

  if (idx < _blocks.size()) {
    _blocks[idx] = blockId;

    onRowUpdated(y);
  }
}


void Board::reset() {
  _blocks.assign(_rows*_columns, kEmptyBlock);
  _fullRows.assign(_rows, 0);

  for (int c = 0; c < _columns; ++c) {
    _blocks[c] = BlockId_Wall;
  }

  for (int r = 0; r < _rows; ++r) {
    _blocks[(r*_columns)] = BlockId_Wall;
    _blocks[((r+1)*_columns)-1] = BlockId_Wall;
  }
}

void Board::render(Renderer& renderer, float clearingPercent) {
  const float blinkFactor = (sinf(M_PI*clearingPercent*10.0f) + 1.0f) * 0.35f;

  for (int r = 0; r < _rows; ++r) {
    const float blink = _fullRows[r] != 0 ? blinkFactor : 0.0f;

    for (int c = 0; c < _columns; ++ c) {
      auto block = _blocks[(r*_columns)+c];

      if (block != kEmptyBlock) {
        const bool wall = (block == BlockId_Wall);
        const glm::vec2 blockPosition = _origin + glm::vec2(c*_blockSize, r*_blockSize);
        renderer.drawBlock(blockPosition, (BlockId)block, wall ? 0.0f : blink);
      }
    }
  }
}

void Board::onRowUpdated(int r) {
  const int start = (r*_columns)+1;
  const int end = ((r+1)*_columns)-1;

  bool fullRow = true;
  for (int idx = start; idx < end; ++idx) {
    fullRow &= (_blocks[idx] != kEmptyBlock);
  }

  if (fullRow)
    _fullRows[r] = 1;
}
