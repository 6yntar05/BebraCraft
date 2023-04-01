#pragma once

#include <array>
#include <vector>

#include "engine/objects/base.h"
#include "engine/objects/mesh.h"

namespace bebra::objects {

using chunkRow = std::array<bebra::objects::Object*, 16>;
using chunkLayer = std::array<chunkRow, 16>;
using chunk = std::vector<chunkLayer>;

class Chunk {
  private:
    // Raw data:
    chunk rawChunk;             // Maybe pointer or function to worldmap

    // Loading params:
    static constexpr uint quantHeight = 16; // split chunk by height and gen mesh for every piece

  public:
    // Chunk contants:
    static constexpr uint lenght  = 16;
    static constexpr uint widht   = 16;
    //static constexpr uint height  = 256;

    // Chunk:
    // struct ? {
    Mesh meshSolid;             // Be drawn first
    Mesh meshTransparent;       // ... second
    Mesh meshSemitransparent;   // ... third
    int x;
    int y;

    // Service
    Chunk() {}
    void meshGen() {}
};

} // namespace bebra::objects