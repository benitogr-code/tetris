#include "game_app.h"

#include <glad/glad.h>

struct Vertex {
  glm::vec2 position;
  glm::vec2 textCoords;
};

bool GameApp::onInit() {
  _blockAtlas.init();

  constexpr int vertexCount = 4 * BlockId_Count;
  constexpr int indexCount = 6 * BlockId_Count;

  std::array<Vertex, vertexCount> vertices;
  std::array<uint32_t, indexCount> indices;
  for (uint8_t i = 0; i < BlockId_Count; ++i) {
    auto block = _blockAtlas.getBlockInfo((BlockId)i);
    auto pos = block.offset - glm::vec2(0.5f);

    vertices[(i*4)] = { {pos.x + block.size, pos.y + block.size}, {block.offset.s + block.size, block.offset.t + block.size}};
    vertices[(i*4)+1] = { {pos.x + block.size, pos.y}, {block.offset.s + block.size, block.offset.t}};
    vertices[(i*4)+2] = { {pos.x, pos.y}, {block.offset.s, block.offset.t}};
    vertices[(i*4)+3] = { {pos.x, pos.y + block.size}, {block.offset.s, block.offset.t + block.size}};

    uint32_t base = (i*4);
    indices[(i*6)] = base;
    indices[(i*6)+1] = base+1;
    indices[(i*6)+2] = base+3;
    indices[(i*6)+3] = base+1;
    indices[(i*6)+4] = base+2;
    indices[(i*6)+5] = base+3;
  }

  const BufferLayout layout({
    { BufferItemType::Float2, "position" },
    { BufferItemType::Float2, "textCoords" },
  });
  _vertexData = VertexArray::Create(
    VertexBuffer::Create(vertices.data(), sizeof(Vertex)*vertices.max_size(), layout),
    IndexBuffer::Create(indices.data(), indices.max_size())
  );

  ShaderCreateParams shaderParams;
  shaderParams.name = "test";
  shaderParams.vertexShaderPath = "shaders/test.vs";
  shaderParams.fragmentShaderPath = "shaders/test.fs";
  _shader = Shader::Create(shaderParams);

  _camera.setAspectRatio(1.6f/0.9f);

  return true;
}

void GameApp::onShutdown() {
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
}

void GameApp::onUpdate(const UpdateContext& ctx) {
  static float time = 0.0f;

  time += ctx.frameTime;

  const float zoom = sinf(time) + 1.25f;
  _camera.setZoom(zoom);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _blockAtlas.getTexture()->bind();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", _camera.getViewProjectionMatrix());
  _vertexData->bind();
  glDrawElements(GL_TRIANGLES, _vertexData->indexCount(), GL_UNSIGNED_INT, 0);

  _vertexData->unbind();
}
