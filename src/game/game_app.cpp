#include "game_app.h"

#include <glad/glad.h>

bool GameApp::onInit() {
  float vertices[] = {
    // positions         texture coords
     0.5f,  0.5f, 0.7f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left
  };
  unsigned int indices[] = {
      0, 1, 3,   // 1st triangle
      1, 2, 3    // 2nd triangle
  };

  const BufferLayout layout({
    { BufferItemType::Float3, "position" },
    { BufferItemType::Float2, "textCoords" },
  });
  _vertexData = VertexArray::Create(
    VertexBuffer::Create(vertices, sizeof(vertices), layout),
    IndexBuffer::Create(indices, 6)
  );

  ShaderCreateParams shaderParams;
  shaderParams.name = "test";
  shaderParams.vertexShaderPath = "shaders/test.vs";
  shaderParams.fragmentShaderPath = "shaders/test.fs";
  _shader = Shader::Create(shaderParams);

  TextureCreateParams textureParams;
  textureParams.filePath = "textures/blocks.png";
  _texture = Texture::Create(textureParams);

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

  const float sinValue = sinf(time);
  const float zoom = sinValue + 1.25f;

  //_camera.setPosition({0.0f, -sinValue * 0.6f});
  _camera.setZoom(zoom);

  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _texture->bind();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", _camera.getViewProjectionMatrix());
  _vertexData->bind();
  glDrawElements(GL_TRIANGLES, _vertexData->indexCount(), GL_UNSIGNED_INT, 0);

  _vertexData->unbind();
}
