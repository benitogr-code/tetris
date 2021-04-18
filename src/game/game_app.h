#pragma once

#include "system/application.h"

class GameApp: public Application {
protected:
  // Application
  virtual bool onInit() override;
  virtual void onShutdown() override;
  virtual void onInputEvent(const InputEvent& event) override;
  virtual void onUpdate() override;
};
