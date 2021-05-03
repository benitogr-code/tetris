#include "tetromino.h"

#include <random>

static std::random_device gRandomDevice;
static std::mt19937 gRandomGen(gRandomDevice());
static std::uniform_int_distribution<> gDistribution(0, 1024);

static int RandShapeId() { return gDistribution(gRandomGen)%7; }
static int RandBlockId() { return gDistribution(gRandomGen)%BlockId_Wall; }
static int RandFrameId() { return gDistribution(gRandomGen)%4; }

Tetromino::Shape Tetromino::Shape::GetShape(int idx) {
  Tetromino::Shape shape;

  if (idx == 0) {
    shape.data[0] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      1, 1, 1, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      1, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 1, 0,
      0, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      0, 1, 1, 0,
      0, 1, 0, 0 };
  }
  else if (idx == 1) {
    shape.data[0] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 1, 1,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 1, 1,
      0, 0, 0, 0 };
  }
  else if (idx == 2) {
    shape.data[0] = {
      0, 0, 0, 0,
      0, 1, 1, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      1, 0, 0, 0,
      1, 1, 1, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      1, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 1, 0,
      0, 0, 1, 0 };
  }
  else if (idx == 3) {
    shape.data[0] = {
      0, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 1, 0,
      1, 0, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 1, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 0, 1, 0,
      1, 1, 1, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 4) {
    shape.data[0] = {
      0, 0, 0, 0,
      0, 1, 1, 0,
      1, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      1, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      0, 1, 1, 0,
      1, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 1, 0 };
  }
  else if (idx == 5) {
    shape.data[0] = {
      0, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      0, 1, 0, 0,
      1, 1, 0, 0,
      1, 0, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 1, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 0, 1, 0,
      0, 1, 1, 0,
      0, 1, 0, 0 };
  }
  else {
    shape.data[0] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 0, 0,
      1, 1, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 0, 0,
      1, 1, 0, 0 };
    shape.data[2] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 0, 0,
      1, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      0, 0, 0, 0,
      1, 1, 0, 0,
      1, 1, 0, 0 };
  }

  return shape;
}

Tetromino::Tetromino(float blockSize)
  : _blockSize(blockSize) {
  randomize();
}

void Tetromino::randomize() {
  _blockId = (BlockId)RandBlockId();
  _shape = Shape::GetShape(RandShapeId());
  _frameId = RandFrameId();
}

void Tetromino::rotate() {
  _frameId = (_frameId+1) % FrameCount;
}

void Tetromino::setPosition(const glm::vec2& pos) {
  _position = pos;
}

void Tetromino::getBlockCoordinates(const glm::ivec2& offset, std::vector<glm::ivec2>& coords) const {
  const auto& shapeData = _shape.data[_frameId];
  coords.clear();

  for (int x = 0; x < 4; ++x) {
    for (int y = 0; y < 4; ++y) {
      const int idx = (x*4) + y;

      if (shapeData[idx] != 0) {
        coords.push_back(offset + glm::ivec2(y, x));
      }
    }
  }
}

void Tetromino::getBlockCoordinatesAfterRotation(const glm::ivec2& offset, std::vector<glm::ivec2>& coords) const {
  const auto& shapeData = _shape.data[(_frameId+1)%FrameCount];
  coords.clear();

  for (int x = 0; x < 4; ++x) {
    for (int y = 0; y < 4; ++y) {
      const int idx = (x*4) + y;

      if (shapeData[idx] != 0) {
        coords.push_back(offset + glm::ivec2(y, x));
      }
    }
  }
}

void Tetromino::render(Renderer& renderer) {
  for (int x = 0; x < 4; ++x) {
    for (int y = 0; y < 4; ++y) {
      const int idx = (x*4) + y;

      if (_shape.data[_frameId][idx] != 0) {
        const glm::vec2 blockPosition = _position + glm::vec2(y*_blockSize, x*_blockSize);
        renderer.drawBlock(blockPosition, _blockId);
      }
    }
  }
}
