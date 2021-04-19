#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
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
  auto shader = std::make_shared<Shader>(params.name);

  std::ifstream vsFile, fsFile;
  vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vsFile.open(params.vertexShaderPath);
    fsFile.open(params.fragmentShaderPath);

    std::stringstream vsStream, fsStream;
    vsStream << vsFile.rdbuf();
    fsStream << fsFile.rdbuf();

    vsFile.close();
    fsFile.close();

    shader->buildFromSources(vsStream.str().c_str(), fsStream.str().c_str());
  }
  catch (std::ifstream::failure& e) {
    LOG_ERROR("Error loading shader '{0}'. Reason: {1}", params.name, e.code().message());
  }

  return shader;
}
