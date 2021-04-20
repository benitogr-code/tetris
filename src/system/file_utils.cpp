#include "file_utils.h"

#include <filesystem>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

std::string FileUtils::_assetsFolder;

void FileUtils::init() {
  auto path = std::filesystem::current_path();
  _assetsFolder = path.parent_path().generic_string().append("/assets/");

  LOG_INFO("Assets folder path: {}", _assetsFolder);
}

bool FileUtils::readTextFile(const char* filePath, std::vector<char>& data) {
  const auto absolutePath = getAbsolutePath(filePath);
  std::ifstream inStream(absolutePath);

  if (!inStream) {
    LOG_WARN("Failed to open text file {}", absolutePath);
    return false;
  }

  inStream.seekg(0, inStream.end);
  const size_t fileLength = inStream.tellg();
  inStream.seekg(0, inStream.beg);

  data.resize(fileLength+1);

  inStream.read(data.data(), fileLength);
  data[fileLength] = '\0';

  inStream.close();

  return true;
}

bool FileUtils::readPngFile(const char* filePath, ImageData& data) {
  const auto absolutePath = getAbsolutePath(filePath);

  const int kRequiredComponents = 4;
  int width, height, components;

  stbi_set_flip_vertically_on_load(true);
  unsigned char* pData = stbi_load(absolutePath.c_str(), &width, &height, &components, kRequiredComponents);

  if (pData == nullptr) {
    LOG_WARN("Failed to load image file {}", absolutePath);
    return false;
  }

  const size_t imgSize = kRequiredComponents * width * height;
  data.data.resize(imgSize);
  data.data.assign(pData, pData + (imgSize - 1));
  data.width = width;
  data.height = height;
  data.bytesPerPixel = components;

  STBI_FREE(pData);

  return true;
}

std::string FileUtils::getAbsolutePath(const char* filePath) {
  return _assetsFolder + filePath;
}
