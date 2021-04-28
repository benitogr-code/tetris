#pragma once

#include "system/graphics/buffers.h"
#include "system/graphics/shader.h"
#include "system/graphics/texture.h"

enum BlockId: uint32_t {
  BlockId_Blue = 0,
  BlockId_Red,
  BlockId_Green,
  BlockId_Cyan,
  BlockId_Orange,
  BlockId_Yellow,
  BlockId_Purple,
  BlockId_Wall,
  BlockId_Count,
};

class BlockRenderer {
private:
  struct BlockVertex {
    glm::vec2 position;
    glm::vec2 textureCoords;
  };

  struct BlockInstance {
    glm::vec2 translation;
    uint32_t  blockId;
  };

public:
  BlockRenderer(float blockSize);
  void init();

  float getBlockSize() const { return _blockSize; }

  void beginFrame(const glm::mat4x4& viewProjection);
  void endFrame();
  void drawBlock(const glm::vec2& position, BlockId id);

private:
  ShaderRef  _shader;
  TextureRef _texture;
  VertexBufferRef _vbBlocks;
  VertexArrayRef  _va;

  std::vector<BlockInstance> _blocks;

  glm::mat4x4 _viewProjection;
  float       _blockSize;
};
