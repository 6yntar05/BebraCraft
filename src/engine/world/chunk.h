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
    const objects::chunk* const rawChunk;   // Source data

    // Loading params:
    static constexpr unsigned int quantHeight = 16; // split chunk by height and gen mesh for every piece

public:
    // Chunk contants:
    static constexpr unsigned int lenght  = 16;
    static constexpr unsigned int widht   = 16;
    //static constexpr unsigned int height  = 256;

    // Chunk:
    // struct ? {
    objects::Mesh meshSolid;             // Be drawn first
    objects::Mesh meshTransparent;       // ... second
    objects::Mesh meshSemitransparent;   // ... third
    // Coordinates in world
    const int x;
    const int y;

    // Service
    void meshGen() { // simple for now
		for (unsigned int iLayer = 0; iLayer < rawChunk->size(); iLayer++) {
			auto& layer = rawChunk->at(iLayer);
			for (unsigned int iRow = 0; iRow < layer.size(); iRow++) {
				auto& row = layer.at(iRow);
				for (unsigned int iObj = 0; iObj < row.size(); iObj++) {
					auto& obj = row.at(iObj);

					if (obj->id == objects::esolid)
						meshSolid.append(*obj, {iObj, iLayer, iRow});
					if (obj->id == objects::etransparent || obj->id == objects::eplant)
						meshTransparent.append(*obj, {iObj, iLayer, iRow});
					if (obj->id == objects::esemitransparent || obj->id == objects::efluid)
						meshSemitransparent.append(*obj, {iObj, iLayer, iRow});
                    
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