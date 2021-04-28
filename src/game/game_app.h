#pragma once

#include "system/application.h"
#include "system/graphics/camera_orthographic.h"

#include "tetris/blocks.h"
#include "tetris/tetromino.h"

class GameApp: public Application {
protected:
  // Application
  virtual bool onInit() override;
  virtual void onShutdown() override;
  virtual void onInputEvent(const InputEvent& event) override;
  virtual void onUpdate(const UpdateContext& ctx) override;

private:
  CameraOrthographic _camera;
  BlocksMaterialRef _blocksMaterial;
  Tetromino  _tetrominoA;
  Tetromino  _tetrominoB;
};
