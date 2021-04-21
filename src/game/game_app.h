#pragma once

#include "system/application.h"
#include "system/graphics/buffers.h"
#include "system/graphics/shader.h"
#include "system/graphics/texture.h"

class GameApp: public Application {
protected:
  // Application
  virtual bool onInit() override;
  virtual void onShutdown() override;
  virtual void onInputEvent(const InputEvent& event) override;
  virtual void onUpdate() override;

private:
  ShaderRef  _shader;
  TextureRef _texture;
  VertexArrayRef _vertexData;
};
