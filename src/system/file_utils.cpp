#include "file_utils.h"

#include <filesystem>
#include <fstream>

std::string FileUtils::_assetsFolder;

void FileUtils::init() {
  auto path = std::filesystem::current_path();
  _assetsFolder = path.parent_path().generic_string().append("/assets/");

  LOG_INFO("Assets folder path: {}", _assetsFolder);
}

bool FileUtils::readTextFile(const char* filePath, std::vector<char>& buffer) {
  const auto absolutePath = getAbsolutePath(filePath);
  std::ifstream inStream(absolutePath);

  if (!inStream) {
    LOG_WARN("Failed to open file {}", absolutePath);
    return false;
  }

  inStream.seekg(0, inStream.end);
  const size_t fileLength = inStream.tellg();
  inStream.seekg(0, inStream.beg);

  buffer.resize(fileLength+1);

  inStream.read(buffer.data(), fileLength);
  buffer[fileLength] = '\0';

  inStream.close();

  return true;
}

std::string FileUtils::getAbsolutePath(const char* filePath) {
  return _assetsFolder + filePath;
}
