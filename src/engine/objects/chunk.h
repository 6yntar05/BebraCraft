#pragma once

#include <array>
#include <vector>

#include "engine/objects/block.h"

namespace bebra {
namespace objects {
    using chunkRow = std::array<bebra::objects::block, 16>;
    using chunkLayer = std::array<chunkRow, 16>;
    using chunk = std::vector<chunkLayer>;
}
}