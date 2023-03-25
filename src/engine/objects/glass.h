#pragma once

#include "engine/objects/base.h"
#include "engine/objects/block.h"

namespace bebra {
namespace objects {

    class glass : public block {
      public:
        // Service
        static constexpr objIdent id = objIdent::eglass;
        glass() : block(id) {};
        glass(objectTexture texture, float rotate = 0.0)
            : glass()
        {
            this->texture = texture;
            this->rotate = rotate;
        }
    };

}
}