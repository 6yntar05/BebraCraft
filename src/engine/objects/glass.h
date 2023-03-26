#pragma once

#include "engine/objects/base.h"
#include "engine/objects/block.h"

namespace bebra::objects {

class Glass : public Block {
    public:
    // Service
    static constexpr ObjIdent id = ObjIdent::eglass;
    Glass() : Block(id) {};
    Glass(ObjectTexture texture, float rotate = 0.0)
    : Glass() {
        this->texture = texture;
        this->rotate = rotate;
    }
};

} // namespace bebra::objects