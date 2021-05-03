#include "renderer.h"

#include <glad/glad.h>

static constexpr int   kMaxBlocks = 1024;
static constexpr float kBlockTexturePadding =  8.0f/128.0f;
static constexpr float kBlockTextureSize    = 32.0f/128.0f;

static constexpr int kMessageMaxLength = 128;
static constexpr int kCharVertices     = 6;

Renderer::Renderer(float blockSize, int fontSize) {
  _blocksBatch.reserve(kMaxBlocks);
  _blockSize = blockSize;
  _messagesBatch.reserve(32);
  _fontSize = fontSize;
  _viewProjection = glm::mat4x4(1.0f);
}

void Renderer::init() {
  // Enable blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Textures
  TextureCreateParams textureParams;
  textureParams.filePath = "textures/blocks.png";
  _blockTexture = Texture::Create(textureParams);

  _fontAtlas = Font::loadFont("fonts/meslo_lgs_bold.ttf", _fontSize);

  // Shaders
  ShaderCreateParams shaderParams;
  shaderParams.name = "text";
  shaderParams.vertexShaderPath = "shaders/text.vs";
  shaderParams.fragmentShaderPath = "shaders/text.fs";
  _textShader = Shader::Create(shaderParams);

  shaderParams.name = "blocks";
  shaderParams.vertexShaderPath = "shaders/blocks.vs";
  shaderParams.fragmentShaderPath = "shaders/blocks.fs";
  _blocksShader = Shader::Create(shaderParams);
  _blocksShader->use();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; ++j) {
      const int index = (i*3) + j;

      if (index < BlockId_Count) {
        std::string name = "u_blockOffsets[" + std::to_string(index) + "]";
        glm::vec2 offset;
        offset.s = ((j+1)*kBlockTexturePadding) + ((j)*kBlockTextureSize);
        offset.t = ((3-i)*kBlockTexturePadding) + ((2-i)*kBlockTextureSize);

        _blocksShader->setUniformVec2(name.c_str(), offset);
      }
    }
  }

  // Geometry buffers
  std::array<BlockVertex, 4> vertices;
  vertices[0] = { glm::vec2(_blockSize, _blockSize), glm::vec2(kBlockTextureSize, kBlockTextureSize) };
  vertices[1] = { glm::vec2(_blockSize, 0.0f), glm::vec2(kBlockTextureSize, 0.0f) };
  vertices[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
  vertices[3] = { glm::vec2(0.0f, _blockSize), glm::vec2(0.0f, kBlockTextureSize) };
  const std::array<uint32_t, 6> indices = {
    0, 1, 3,
    1, 2, 3
  };

  auto vbQuad = VertexBuffer::Create(
    vertices.data(),
    sizeof(BlockVertex)*4,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _vbBlocks = VertexBuffer::Create(
    sizeof(BlockInstance) * kMaxBlocks,
    BufferLayout({
      { BufferItemType::Float2, "translation" },
      { BufferItemType::Int, "blockId" },
    })
  );
  _vbBlocks->setFlag(VertexBuffer::Flag_Instance);

  _vaBlocks = VertexArray::Create();
  _vaBlocks->addVertextBuffer(vbQuad);
  _vaBlocks->addVertextBuffer(_vbBlocks);
  _vaBlocks->setIndexBuffer(
    IndexBuffer::Create(indices.data(), sizeof(uint32_t)*indices.max_size())
  );

  _vbTextQuads = VertexBuffer::Create(
    sizeof(TextVertex) * kCharVertices * kMessageMaxLength,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _vaText = VertexArray::Create();
  _vaText->addVertextBuffer(_vbTextQuads);
}

void Renderer::beginFrame(const glm::mat4x4& viewProjection) {
  _viewProjection = viewProjection;
  _blocksBatch.clear();
  _messagesBatch.clear();
}

void Renderer::endFrame() {
  glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  if (_blocksBatch.size() > 0) {
    auto blockCount = _blocksBatch.size();
    _vbBlocks->uploadData(_blocksBatch.data(), sizeof(BlockInstance)*blockCount);

    _blockTexture->bind();
    _blocksShader->use();
    _blocksShader->setUniformMatrix4("u_viewProjection", _viewProjection);
    _vaBlocks->bind();
    glDrawElementsInstanced(GL_TRIANGLES, _vaBlocks->indexCount(), GL_UNSIGNED_INT, nullptr, blockCount);
    _vaBlocks->unbind();
  }

  if (_messagesBatch.size() > 0) {
    _fontAtlas->bindTexture();
    _textShader->use();
    _textShader->setUniformMatrix4("u_viewProjection", _viewProjection);
    _vaText->bind();

    for (const auto& message: _messagesBatch) {
      _textShader->setUniformVec3("u_textColor", message.color);

      auto vertexCount = message.vertices.size();
      _vbTextQuads->uploadData(message.vertices.data(), sizeof(TextVertex)*vertexCount);

      glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }

    _vaText->unbind();
  }
}

void Renderer::setClearColor(const glm::vec3& color) {
  _clearColor = color;
}

void Renderer::drawBlock(const glm::vec2& position, BlockId id) {
  if (_blocksBatch.size() >= kMaxBlocks)
    return;

  _blocksBatch.push_back({ position, (uint32_t)id });
}

void Renderer::drawText(const std::string& text, const glm::vec2& position, const glm::vec3& color, const float scale, const glm::mat4x4& viewProjection) {
  TextMessage message;
  message.vertices.reserve(kMessageMaxLength * kCharVertices);
  message.color = color;

  const size_t textLength = std::min(text.length(), (size_t)kMessageMaxLength);
  int xOffset = 0;

  for (size_t i = 0; i < textLength; ++i) {
    const unsigned char c = text.at(i);
    auto charInfo = _fontAtlas->getCharacterInfo(c);
    if (charInfo == nullptr)
      continue;

    const float xpos = xOffset + position.x + (charInfo->bearing.x * scale);
    const float ypos = position.y - (charInfo->size.y - charInfo->bearing.y) * scale;

    const float w = charInfo->size.x * scale;
    const float h = charInfo->size.y * scale;
    const auto& offsets = charInfo->atlasOffsets;

    message.vertices.push_back({{ xpos, ypos + h }, { offsets[0], 0.0f }});
    message.vertices.push_back({{ xpos, ypos }, { offsets[0], 1.0f }});
    message.vertices.push_back({{ xpos + w, ypos }, { offsets[1], 1.0f }});
    message.vertices.push_back({{ xpos, ypos + h }, { offsets[0], 0.0f }});
    message.vertices.push_back({{ xpos + w, ypos }, { offsets[1], 1.0f }});
    message.vertices.push_back({{ xpos + w, ypos + h }, { offsets[1], 0.0f }});

    xOffset += charInfo->advance.x * scale;
  }

  if (message.vertices.size() > 0) {
    _messagesBatch.emplace_back(message);
  }
}
