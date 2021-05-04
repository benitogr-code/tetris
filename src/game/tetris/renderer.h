#pragma once

#include "system/font.h"
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

class Renderer {
private:
  struct BlockVertex {
    glm::vec2 position;
    glm::vec2 textureCoords;
  };
  struct BlockInstance {
    glm::vec2 translation;
    uint32_t  blockId;
  };

  struct TextVertex {
    glm::vec2 position;
    glm::vec2 textureCoords;
  };
  struct TextMessage {
    std::vector<TextVertex> vertices;
    glm::vec3 color;
  };

public:
  Renderer(float blockSize, int fontSize);
  void init();

  void beginFrame(const glm::mat4x4& viewProjection);
  void endFrame();
  void setClearColor(const glm::vec3& color);
  void drawBlock(const glm::vec2& position, BlockId id);
  void drawText(const std::string& text, const glm::vec2& position, const glm::vec3& color, const float scale);

private:
  ShaderRef  _blocksShader;
  ShaderRef  _textShader;

  TextureRef   _blockTexture;
  FontAtlasRef _fontAtlas;

  VertexBufferRef _vbBlocks;
  VertexArrayRef  _vaBlocks;
  std::vector<BlockInstance> _blocksBatch;

  VertexBufferRef _vbTextQuads;
  VertexArrayRef  _vaText;
  std::vector<TextMessage> _messagesBatch;

  glm::mat4x4 _viewProjection;
  glm::vec3   _clearColor;
  float       _blockSize;
  int         _fontSize;
};
