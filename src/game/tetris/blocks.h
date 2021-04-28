#pragma once

#include "system/graphics/shader.h"
#include "system/graphics/texture.h"

enum BlockId: int8_t {
  BlockId_Invalid = -1,
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

struct BlockVertex {
  glm::vec2 position;
  glm::vec2 textureCoords;
};

struct BlockInstance {
  glm::vec2 translation;
  uint32_t  blockId;
};

void createBlockQuad(float size, std::array<BlockVertex, 4>& vertices, std::array<uint32_t, 6>& indices);

class BlocksMaterial {
public:
  BlocksMaterial();

  void init();
  ShaderRef getShader() { return _shader; }
  TextureRef getTexture() { return _texture; }

private:
  ShaderRef  _shader;
  TextureRef _texture;
};

typedef std::shared_ptr<BlocksMaterial> BlocksMaterialRef;
