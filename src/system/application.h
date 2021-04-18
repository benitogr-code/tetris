#pragma once

#include "input.h"
#include "window.h"

class Application {
public:
  Application();
  virtual ~Application();

  bool init(const WindowDesc& desc);
  void shutdown();
  void run();

protected:
  // To be implemented by custom application
  virtual bool onInit() = 0;
  virtual void onShutdown() = 0;
  virtual void onInputEvent(const InputEvent& event) = 0;
  virtual void onUpdate() = 0;

private:
  void checkSystemEvents();

private:
  std::unique_ptr<Window> _window;
  std::unique_ptr<Input> _input;
  bool _running;
};

typedef std::function<Application* ()> ApplicationCreator;

struct StartupParams {
  ApplicationCreator appCreatorFunc;
  WindowDesc windowDesc;
};

int startApplication(const StartupParams& params);
