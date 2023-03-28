#pragma once
#include <iostream>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace bebra::utils {

class Font {
  private:

  public:
    void render(std::string text, uint x = 0, uint y = 0, void* mode = nullptr) {
    }

    Font(std::string path, uint size) {
    }

    ~Font() {
    }
};

} // namespace bebra::utils
