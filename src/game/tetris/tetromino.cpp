#include "tetromino.h"

#include <random>

static std::random_device gRandomDevice;
static std::mt19937 gRandomGen(gRandomDevice());
static std::uniform_int_distribution<> gShapeDistr(0, 6);
static std::uniform_int_distribution<> gBlockDistr(BlockId_Blue, BlockId_Purple);
static std::uniform_int_distribution<> gFrameDistr(0, 3);

static int RandShapeId() { return gShapeDistr(gRandomGen); }
static int RandBlockId() { return gBlockDistr(gRandomGen); }
static int RandFrameId() { return gFrameDistr(gRandomGen); }

Tetromino::Shape Tetromino::Shape::GetShape(int idx) {
  Tetromino::Shape shape;

  if (idx == 0) {
    shape.data[0] = {
      0, 0, 0, 0,
      1, 1, 1, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 1, 0, 0,
      1, 1, 0, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 1, 0, 0,
      1, 1, 1, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      0, 1, 0, 0,
      0, 1, 1, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 1) {
    shape.data[0] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      1, 1, 1, 1,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      1, 1, 1, 1,
      0, 0, 0, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 2) {
    shape.data[0] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 0, 0, 0,
      1, 1, 1, 0,
      1, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      1, 1, 0, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      0, 0, 1, 0,
      1, 1, 1, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 3) {
    shape.data[0] = {
      0, 1, 0, 0,
      0, 1, 0, 0,
      1, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      1, 0, 0, 0,
      1, 1, 1, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 1, 1, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      0, 0, 0, 0,
      1, 1, 1, 0,
      0, 0, 1, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 4) {
    shape.data[0] = {
      0, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      0, 1, 0, 0,
      1, 1, 0, 0,
      1, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      1, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      0, 0, 1, 0,
      0, 1, 0, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
  }
  else if (idx == 5) {
    shape.data[0] = {
      0, 0, 0, 0,
      0, 1, 1, 0,
      1, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      1, 0, 0, 0,
      1, 1, 0, 0,
      0, 1, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      0, 1, 1, 0,
      1, 1, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      0, 1, 0, 0,
      0, 1, 1, 0,
      0, 0, 1, 0,
      0, 0, 0, 0 };
  }
  else {
    shape.data[0] = {
      1, 1, 0, 0,
      1, 1, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[1] = {
      1, 1, 0, 0,
      1, 1, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[2] = {
      1, 1, 0, 0,
      1, 1, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
    shape.data[3] = {
      1, 1, 0, 0,
      1, 1, 0, 0,
      0, 0, 0, 0,
      0, 0, 0, 0 };
  }

  return shape;
}

Tetromino::Tetromino() {
  _shape = Shape::GetShape(0);
}

void Tetromino::init(float size, BlocksMaterialRef material) {
  _material = material;
  _size = size;
  _updateVertexData = true;

  std::array<BlockVertex, 4> vertices;
  std::array<uint32_t, 6> indices;
  createBlockQuad(size, vertices, indices);

  _quad = VertexBuffer::Create(
    vertices.data(),
    sizeof(BlockVertex)*4,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _instanceData = VertexBuffer::Create(
    sizeof(BlockInstance)*16,
    BufferLayout({
      { BufferItemType::Float2, "translation" },
      { BufferItemType::Int, "blockId" },
    })
  );
  _instanceData->setFlag(VertexBuffer::Flag_Instance);

  _vertexData = VertexArray::Create();
  _vertexData->addVertextBuffer(_quad);
  _vertexData->addVertextBuffer(_instanceData);
  _vertexData->setIndexBuffer(
    IndexBuffer::Create(indices.data(), sizeof(uint32_t)*indices.max_size())
  );
}

void Tetromino::randomize() {
  _id = RandBlockId();
  _shape = Shape::GetShape(RandShapeId());
  _frameId = RandFrameId();
  _updateVertexData = true;
}

void Tetromino::rotate() {
  _frameId = (_frameId+1) % FrameCount;
  _updateVertexData = true;
}

void Tetromino::setPosition(const glm::vec2& pos) {
  _position = pos;
  _updateVertexData = true;
}

void Tetromino::render(RenderDevice& renderDevice) {
  if (_updateVertexData) {
    _updateVertexData = false;

    std::vector<BlockInstance> instances;
    instances.reserve(4);

    for (int x = 0; x < 4; ++x) {
      for (int y = 0; y < 4; ++y) {
        const int idx = (x*4) + y;
        if (_shape.data[_frameId][idx] != 0) {
          glm::vec2 pos = _position + glm::vec2(y * _size,  x * -_size);
          instances.push_back({ pos, _id });
        }
      }
    }

    _instanceData->uploadData(instances.data(), sizeof(BlockInstance)*instances.size());
  }

  _material->getTexture()->bind();
  renderDevice.drawInstanced(_vertexData, _material->getShader(), 4);
}
