#pragma once

#include "graphics/buffers.h"
#include "graphics/shader.h"

class RenderDevice {
public:
  void init();

  void beginRendering(const glm::mat4x4& viewProjection);

  void clear(float r, float g, float b);
  void draw(VertexArrayRef vertexArray, ShaderRef shader);
  void drawInstanced(VertexArrayRef vertexArray, ShaderRef shader, uint32_t count);
private:

  glm::mat4x4 _viewProjection;
};
