#include <functional>

class Application {
public:
  Application();
  virtual ~Application();

  bool init();
  void shutdown();
  void run();

protected:
  virtual bool onInit() = 0;
  virtual void onShutdown() = 0;
  virtual void onUpdate() = 0;

private:
  bool _running;
};

typedef std::function<Application* ()> ApplicationCreator;

struct StartupParams {
  ApplicationCreator appCreatorFunc;
};

int startApplication(const StartupParams& params);
