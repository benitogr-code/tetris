#include "render_device.h"

#include <glad/glad.h>

void RenderDevice::init() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _viewProjection = glm::mat4x4(1.0f);
}

void RenderDevice::beginRendering(const glm::mat4x4& viewProjection) {
  _viewProjection = viewProjection;
}

void RenderDevice::clear(float r, float g, float b) {
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void RenderDevice::draw(VertexArrayRef vertexArray, ShaderRef shader) {
  shader->use();
  shader->setUniformMatrix4("u_viewProjection", _viewProjection);
  vertexArray->bind();
  glDrawElements(GL_TRIANGLES, vertexArray->indexCount(), GL_UNSIGNED_INT, 0);
  vertexArray->unbind();
}

void RenderDevice::drawInstanced(VertexArrayRef vertexArray, ShaderRef shader, uint32_t count) {
  shader->use();
  shader->setUniformMatrix4("u_viewProjection", _viewProjection);
  vertexArray->bind();
  glDrawElementsInstanced(GL_TRIANGLES, vertexArray->indexCount(), GL_UNSIGNED_INT, nullptr, count);
  vertexArray->unbind();
}
