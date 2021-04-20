#include "shader.h"
#include "system/file_utils.h"

#include <glad/glad.h>

// Helpers

static void checkCompileErrors(GLuint shader, const char* type) {
  GLint success;
  GLchar infoLog[1024];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(shader, 1024, NULL, infoLog);
    LOG_ERROR("Shader compile error: Type {0}, Info: {1}", type, infoLog);
  }
}

static void checkLinkErrors(GLuint shader, const char* name) {
  GLint success;
  GLchar infoLog[1024];

  glGetProgramiv(shader, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(shader, 1024, NULL, infoLog);
    LOG_ERROR("Shader link error: Name {0}, Info: {1}", name, infoLog);
  }
}

// Shader

Shader::Shader(const char* name)
  : _name(name)
  , _id(0) {

}

Shader::~Shader() {
  glDeleteProgram(_id);
}

void Shader::use() {
  glUseProgram(_id);
}

void Shader::buildFromSources(const char* vsSources, const char* fsSources) {
  // Vertex Shader
  unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vsSources, NULL);
  glCompileShader(vertex);
  checkCompileErrors(vertex, "Vertex");

  // Fragment Shader
  unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fsSources, NULL);
  glCompileShader(fragment);
  checkCompileErrors(fragment, "Fragment");

  // Shader Program
  _id = glCreateProgram();
  glAttachShader(_id, vertex);
  glAttachShader(_id, fragment);

  glLinkProgram(_id);
  checkLinkErrors(_id, _name.c_str());

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

/*static*/ ShaderRef Shader::Create(const ShaderCreateParams& params) {
  ShaderRef shader(new Shader(params.name));

  std::vector<char> vsBuffer, fsBuffer;
  if (FileUtils::readTextFile(params.vertexShaderPath, vsBuffer)
    && FileUtils::readTextFile(params.fragmentShaderPath, fsBuffer)) {

    shader->buildFromSources(vsBuffer.data(), fsBuffer.data());
  }
  else {
    LOG_ERROR("Error loading shader '{}'", params.name);
  }

  return shader;
}
