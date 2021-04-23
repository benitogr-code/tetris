#include "camera_orthographic.h"

CameraOrthographic::CameraOrthographic()
  : CameraOrthographic(1.0f) {
}

CameraOrthographic::CameraOrthographic(float aspectRatio, float zoom /*= 1.0f*/)
  : _aspectRatio(aspectRatio)
  , _zoom(1.0f) {

  const float h = aspectRatio * zoom;
  const float v = zoom;

  _projectionMatrix = glm::ortho(-h, h, -v, v);
  _viewMatrix = glm::identity<glm::mat4x4>();
  _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
  _position = glm::vec2(0.0f);
}

void CameraOrthographic::setAspectRatio(float aspectRatio) {
  const float h = aspectRatio * _zoom;
  const float v = _zoom;

  _aspectRatio = aspectRatio;
  _projectionMatrix = glm::ortho(-h, h, -v, v);
  updateViewMatrices();
}

void CameraOrthographic::setZoom(float zoom) {
  const float h = _aspectRatio * zoom;
  const float v = zoom;

  _zoom = zoom;
  _projectionMatrix = glm::ortho(-h, h, -v, v);
  updateViewMatrices();
}

void CameraOrthographic::setPosition(const glm::vec2& position) {
  _position = position;
  updateViewMatrices();
}

void CameraOrthographic::updateViewMatrices() {
  const auto transform = glm::translate(glm::mat4x4(1.0f), glm::vec3(_position, 0.0f));

  _viewMatrix = glm::inverse(transform);
  _viewProjectionMatrix = _projectionMatrix * _viewMatrix;
}
