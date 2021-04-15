#include "window.h"

class Application {
public:
  Application();
  virtual ~Application();

  bool init(const WindowDesc& desc);
  void shutdown();
  void run();

protected:
  virtual bool onInit() = 0;
  virtual void onShutdown() = 0;
  virtual void onUpdate() = 0;

private:
  std::unique_ptr<Window> _window;
  bool _running;
};

typedef std::function<Application* ()> ApplicationCreator;

struct StartupParams {
  ApplicationCreator appCreatorFunc;
  WindowDesc windowDesc;
};

int startApplication(const StartupParams& params);
