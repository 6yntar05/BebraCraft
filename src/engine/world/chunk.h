#pragma once

#include <array>
#include <vector>

#include "engine/objects/base.h"
#include "engine/objects/mesh.h"

namespace bebra::objects {
using chunkRow = std::array<bebra::objects::Object*, 16>;
using chunkLayer = std::array<chunkRow, 16>;
using chunk = std::vector<chunkLayer>;
} // namespace bebra::objects

namespace bebra::world {
class Chunk {
  private:
    // Raw data:
    const objects::chunk* const rawChunk;            // Source data

    // Loading params:
    static constexpr uint quantHeight = 16; // split chunk by height and gen mesh for every piece

  public:
    // Chunk contants:
    static constexpr uint lenght  = 16;
    static constexpr uint widht   = 16;
    //static constexpr uint height  = 256;

    // Chunk:
    // struct ? {
    objects::Mesh meshSolid;             // Be drawn first
    objects::Mesh meshTransparent;       // ... second
    objects::Mesh meshSemitransparent;   // ... third
    const int x;
    const int y;

    // Service
    void meshGen() { // simple for now
		for (uint iLayer = 0; iLayer < rawChunk->size(); iLayer++) {
			auto& layer = rawChunk->at(iLayer);
			for (uint iRow = 0; iRow < layer.size(); iRow++) {
				auto& row = layer.at(iRow);
				for (uint iObj = 0; iObj < row.size(); iObj++) {
					auto& obj = row.at(iObj);

					if (obj->id == bebra::objects::ObjIdent::eblock)
						meshSolid.append(*obj, {iObj, iLayer, iRow});

				}
			}
		}
    }

    Chunk(const objects::chunk* const rawChunk, const int x, const int y)
	: rawChunk(rawChunk), x(x), y(y) {
        meshGen();
    }
};

} // namespace bebra::objects