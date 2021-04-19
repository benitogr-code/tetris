#pragma once

class Shader;
typedef std::shared_ptr<Shader> ShaderRef;

struct ShaderCreateParams {
  ShaderCreateParams()
    : name(nullptr)
    , vertexShaderPath(nullptr)
    , fragmentShaderPath(nullptr) {

    }

  const char* name;
  const char* vertexShaderPath;
  const char* fragmentShaderPath;
};

class Shader {
public:
  Shader(const char* name);
  ~Shader();

  void use();
  static ShaderRef Create(const ShaderCreateParams& params);

private:
  void buildFromSources(const char* vsSources, const char* fsSources);

private:
  std::string _name;
  unsigned int _id;
};
