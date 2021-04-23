#pragma once

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

struct BlockInfo {
  glm::vec2 offset;
  float     size;
};

class BlockAtlas {
public:
  BlockAtlas();

  void init();

  const TextureRef& getTexture() const {
    return _texture;
  }
  const BlockInfo& getBlockInfo(BlockId id) const {
    return _blocks[id];
  }

private:
  TextureRef _texture;
  std::array<BlockInfo, BlockId_Count> _blocks;
};
