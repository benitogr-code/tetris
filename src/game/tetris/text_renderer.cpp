#include "text_renderer.h"

#include <glad/glad.h>

#define TEXT_MAX_LENGTH 512
#define CHAR_VERTICES   6

TextRenderer::TextRenderer() {
  _text.reserve(TEXT_MAX_LENGTH*CHAR_VERTICES);
}

void TextRenderer::init(int fontSize) {
  _font = Font::loadFont("fonts/meslo_lgs_bold.ttf", fontSize);

  ShaderCreateParams shaderParams;
  shaderParams.name = "text";
  shaderParams.vertexShaderPath = "shaders/text.vs";
  shaderParams.fragmentShaderPath = "shaders/text.fs";
  _shader = Shader::Create(shaderParams);

  _vbTextQuads = VertexBuffer::Create(
    sizeof(TextVertex)*CHAR_VERTICES*TEXT_MAX_LENGTH,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _va = VertexArray::Create();
  _va->addVertextBuffer(_vbTextQuads);
}

void TextRenderer::drawText(const std::string& text, const glm::vec2& position, const glm::vec3& color, const float scale, const glm::mat4x4& viewProjection) {
  _text.clear();

  int xOffset = 0;
  for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
    auto charInfo = _font->getCharacterInfo(*c);
    if (charInfo == nullptr)
      continue;

    const float xpos = xOffset + position.x + (charInfo->bearing.x * scale);
    const float ypos = position.y - (charInfo->size.y - charInfo->bearing.y) * scale;

    const float w = charInfo->size.x * scale;
    const float h = charInfo->size.y * scale;
    const auto& offsets = charInfo->atlasOffsets;

    _text.push_back({{ xpos, ypos + h }, { offsets[0], 0.0f }});
    _text.push_back({{ xpos, ypos }, { offsets[0], 1.0f }});
    _text.push_back({{ xpos + w, ypos }, { offsets[1], 1.0f }});
    _text.push_back({{ xpos, ypos + h }, { offsets[0], 0.0f }});
    _text.push_back({{ xpos + w, ypos }, { offsets[1], 1.0f }});
    _text.push_back({{ xpos + w, ypos + h }, { offsets[1], 0.0f }});

    xOffset += charInfo->advance.x * scale;
  }

  if (_text.size() == 0)
    return;

  auto charCount = _text.size();
  _vbTextQuads->uploadData(_text.data(), sizeof(TextVertex)*charCount);

  _font->bindTexture();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", viewProjection);
  _shader->setUniformVec3("u_textColor", color);
  _va->bind();
  glDrawArrays(GL_TRIANGLES, 0, charCount);
  _va->unbind();
}
