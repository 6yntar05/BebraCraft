#pragma once

#include <array>
#include <vector>

#include "engine/objects/base.h"

namespace bebra::objects {

using chunkRow = std::array<bebra::objects::Object*, 16>;
using chunkLayer = std::array<chunkRow, 16>;
using chunk = std::vector<chunkLayer>;
// TODO: Complex chunk

} // namespace bebra::objects