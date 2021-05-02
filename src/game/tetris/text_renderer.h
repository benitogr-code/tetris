#pragma once

#include "system/font.h"
#include "system/graphics/buffers.h"
#include "system/graphics/shader.h"

class TextRenderer {
private:
  struct TextVertex {
    glm::vec2 position;
    glm::vec2 textureCoords;
  };

public:
  TextRenderer();

  void init(int fontSize);
  void drawText(const std::string& text, const glm::vec2& position, const glm::vec3& color, const float scale, const glm::mat4x4& viewProjection);

private:
  std::vector<TextVertex> _text;

  ShaderRef    _shader;
  FontAtlasRef _font;
  VertexBufferRef _vbTextQuads;
  VertexArrayRef  _va;
};
