#pragma once

class FontAtlas;
typedef std::shared_ptr<FontAtlas> FontAtlasRef;

struct FT_LibraryRec_;
struct FT_FaceRec_;

class FontAtlas {
public:
  struct CharacterInfo {
    glm::ivec2 advance;
    glm::ivec2 bearing;
    glm::ivec2 bitmapSize;
    float      atlasOffset; // x-offset
  };

public:
  ~FontAtlas();

  static FontAtlasRef Create(FT_LibraryRec_* library, const char* fontFile, int pixelSize);

private:
  FontAtlas() = delete;
  FontAtlas(const FontAtlas&) = delete;
  FontAtlas(FT_FaceRec_* face, int pixelSize);

private:
  std::array<CharacterInfo, 128> _characters;
  uint32_t _textureId = 0;
  int _width = 0;
  int _height = 0;
};
