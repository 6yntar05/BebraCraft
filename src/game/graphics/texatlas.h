#pragma once

#include "engine/graphics/textures.h"
#include <map>

namespace craft {

const std::string path = "textures/resourcepack/assets/minecraft/textures/block/";
using texCords = std::pair<double, double>;

template <typename objectType>
struct textureAtlas {
    const float mosaicSize;
    bebra::graphics::Texture texture;
    std::map<objectType, texCords> relationship;

    textureAtlas(const float mosaicSize);
    texCords getTextureCoords(const objectType& object);
    void appendTexture(const objectType& object);
};

struct textureAtlases {
    textureAtlas<void*> solid;
    textureAtlas<void*> transparent;
    textureAtlas<void*> semitransparent;
    textureAtlas<void*> hudAndParticles;

    void genSolid();
    void genTransparent();
    void genSemitransparent();
    void genHudAndParticles();

    textureAtlases();
};


} // namespace craft