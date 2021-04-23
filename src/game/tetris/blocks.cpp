#include "blocks.h"

BlockAtlas::BlockAtlas() {
}

void BlockAtlas::init() {
  TextureCreateParams params;
  params.filePath = "textures/blocks.png";
  _texture = Texture::Create(params);

  const float padding = 8.0f/128.0f;
  const float blockSize = 32.0f/128.0f;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; ++j) {
      const int index = (i*3) + j;

      if (index < BlockId_Count) {
        _blocks[index].offset.s = ((j+1)*padding) + ((j)*blockSize);
        _blocks[index].offset.t = ((3-i)*padding) + ((2-i)*blockSize);
        _blocks[index].size = blockSize;
      }
    }
  }
}
