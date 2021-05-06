#pragma once

#include "system/application.h"
#include "system/graphics/camera_orthographic.h"

#include "tetris/board.h"
#include "tetris/tetromino.h"
#include "tetris/renderer.h"

enum class GameState {
  PreGame,
  Running,
  Paused,
  GameOver
};

struct GameStats {
  GameStats() {
    reset();
  }

  void reset() {
    score = 0;
    lines = 0;
  }

  int score;
  int lines;
};

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
  void drawGameUI();
  void drawBoard();
  void drawBoardClearing(float clearingPercentage);
  void drawBoardWithMessage(const std::string& message);
  void changeGameState(GameState state);
  void moveTetromino(const glm::ivec2& boardLocation);
  void moveAndRotateTetromino(const glm::ivec2& boardLocation);
  void respawnTetromino();

private:
  CameraOrthographic _camera;
  Renderer           _renderer;

  Board      _board;
  Tetromino  _uiTetromino;
  Tetromino  _boardTetromino;
  glm::ivec2 _boardTetrominoLocation;
  float      _boardTetrominoNextMove;
  float      _boardTetrominoSpeed;

  GameState _gameState = GameState::PreGame;
  GameStats _stats;
  float     _gameTime = 0.0f;
  float     _clearRowsTimeout = -1.0f;
  bool      _clearingRows = false;
};
