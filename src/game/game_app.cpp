#include "game_app.h"

#include <system/graphics/shader.h>
#include <system/graphics/texture.h>
#include <glad/glad.h>

// Global data
static unsigned int gVBO = 0;
static unsigned int gVAO = 0;
static unsigned int gEBO = 0;
static ShaderRef gShader;
static TextureRef gTexture;

bool GameApp::onInit() {
  float vertices[] = {
    // positions         texture coords
     0.5f,  0.5f, 0.7f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // top left
  };
  unsigned int indices[] = {  // note that we start from 0!
      0, 1, 3,   // first triangle
      1, 2, 3    // second triangle
  };

  glGenVertexArrays(1, &gVAO);
  glBindVertexArray(gVAO);

  glGenBuffers(1, &gVBO);
  glBindBuffer(GL_ARRAY_BUFFER, gVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glGenBuffers(1, &gEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  ShaderCreateParams shaderParams;
  shaderParams.name = "test";
  shaderParams.vertexShaderPath = "shaders/test.vs";
  shaderParams.fragmentShaderPath = "shaders/test.fs";
  gShader = Shader::Create(shaderParams);

  TextureCreateParams textureParams;
  textureParams.filePath = "textures/test.png";
  gTexture = Texture::Create(textureParams);

  return true;
}

void GameApp::onShutdown() {
  gShader.reset();
  gTexture.reset();

  glDeleteVertexArrays(1, &gVAO);
  glDeleteBuffers(1, &gVBO);
  glDeleteBuffers(1, &gEBO);
}

void GameApp::onInputEvent(const InputEvent& event) {
  LOG_INFO("onInputEvent: Key {0} | State {1}", event.keyId, event.state);
}

void GameApp::onUpdate() {
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  gTexture->bind();
  gShader->use();
  glBindVertexArray(gVAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glBindVertexArray(0);
}
