#pragma once

#include "system/application.h"
#include "system/graphics/camera_orthographic.h"

#include "tetris/block_renderer.h"
#include "tetris/tetromino.h"

class GameApp: public Application {
public:
  GameApp();

protected:
  // Application
  virtual bool onInit() override;
  virtual void onShutdown() override;
  virtual void onInputEvent(const InputEvent& event) override;
  virtual void onUpdate(const UpdateContext& ctx) override;

private:
  CameraOrthographic _camera;
  BlockRenderer _blockRenderer;
  std::array<Tetromino, 6>  _tetrominos;
};
