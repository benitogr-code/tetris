#include "text_renderer.h"

#include <glad/glad.h>

#define TEXT_MAX_LENGTH 512
#define CHAR_VERTICES   6

TextRenderer::TextRenderer() {
  _text.reserve(TEXT_MAX_LENGTH*CHAR_VERTICES);
}

void TextRenderer::init() {
  _font = Font::loadFont("fonts/pixeloperator-bold.ttf", 64);

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

void TextRenderer::drawText(const std::string& text, const glm::vec2 position, const glm::mat4x4 viewProjection) {
  _text.clear();

  int xOffset = 0;
  for (std::string::const_iterator c = text.begin(); c != text.end(); c++) {
    auto charInfo = _font->getCharacterInfo(*c);
    if (charInfo == nullptr)
      continue;

    const float xpos = xOffset + position.x + charInfo->bearing.x;
    const float ypos = position.y - charInfo->size.y - charInfo->bearing.y;

    const float w = charInfo->size.x;
    const float h = charInfo->size.y;
    _text.push_back({
      { xpos, ypos + h }, { charInfo->atlasOffset, 0.0f }
    });
    _text.push_back({
      { xpos, ypos }, { charInfo->atlasOffset, 1.0f }
    });
    _text.push_back({
      { xpos + w, ypos }, { charInfo->atlasOffset + 0.1f, 1.0f }
    });
    _text.push_back({
      { xpos, ypos + h }, { charInfo->atlasOffset, 0.0f }
    });
    _text.push_back({
      { xpos + w, ypos }, { charInfo->atlasOffset + 0.1f, 1.0f }
    });
    _text.push_back({
      { xpos + w, ypos + h }, { charInfo->atlasOffset + 0.1f, 0.0f }
    });

    xOffset += charInfo->advance.x;
  }

  if (_text.size() == 0)
    return;

  auto charCount = _text.size();
  _vbTextQuads->uploadData(_text.data(), sizeof(TextVertex)*charCount);

  _font->bindTexture();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", viewProjection);
  _va->bind();
  glDrawArrays(GL_TRIANGLES, 0, charCount);
  _va->unbind();
}

void TextRenderer::drawAtlas(const glm::mat4x4 viewProjection) {
  float h = _font->getHeight();
  float w = _font->getWidth();

  float w2 = w / 2.0f;
  std::array<TextVertex, 6> vertices;
  vertices[0] = { glm::vec2(-w2, 200.0f + h),    glm::vec2(0.0f, 0.0f) };
  vertices[1] = { glm::vec2(-w2, 200.0f), glm::vec2(0.0f, 1.0f) };
  vertices[2] = { glm::vec2(w2, 200.0f),  glm::vec2(1.0f, 1.0f) };
  vertices[3] = { glm::vec2(-w2, 200.0f + h),    glm::vec2(0.0f, 0.0f) };
  vertices[4] = { glm::vec2(w2, 200.0f),  glm::vec2(1.0f, 1.0f) };
  vertices[5] = { glm::vec2(w2, 200.0f + h),     glm::vec2(1.0f, 0.0f) };

  _vbTextQuads->uploadData(vertices.data(), sizeof(TextVertex)*6);

  _font->bindTexture();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", viewProjection);
  _va->bind();
  glDrawArrays(GL_TRIANGLES, 0, 6);
  _va->unbind();
}
