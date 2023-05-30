#pragma once

#include <unordered_map>

namespace craft {

class BlockTable {
private:
    std::unordered_map<void*, void*> blocks;

public:
    BlockTable();

};

} // namespace craft