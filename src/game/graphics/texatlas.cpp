#include "game/graphics/texatlas.h"
#include "engine/graphics/textures.h"

namespace craft {

template <> textureAtlas<void*>::textureAtlas(const float mosaicSize)
: mosaicSize(mosaicSize), texture({}), relationship() {

}

} // namespace craft