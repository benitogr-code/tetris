#pragma once

#include "system/application.h"
#include "system/graphics/camera_orthographic.h"

#include "tetris/board.h"
#include "tetris/tetromino.h"
#include "tetris/renderer.h"

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
  void moveTetromino(const glm::ivec2& boardLocation);
  void moveAndRotateTetromino(const glm::ivec2& boardLocation);
  void respawnTetromino();

private:
  CameraOrthographic _camera;
  Renderer _renderer;

  Board _board;
  Tetromino  _tetromino;
  glm::ivec2 _tetrominoBoardLocation;

  Tetromino  _nextTetromino;
};
