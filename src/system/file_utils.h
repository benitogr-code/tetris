#pragma once

class FileUtils {
public:
  static void init();

  static bool readTextFile(const char* filePath, std::vector<char>& data);

private:
  static std::string getAbsolutePath(const char* filePath);

private:
  static std::string _assetsFolder;
};
