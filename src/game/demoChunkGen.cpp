#include <array>
#include <vector>
#include "game/demoChunkGen.h"
#include "engine/objects/objects.h"
#include "engine/graphics/textures.h"

const std::string path = "textures/resourcepack/assets/minecraft/textures/block/";

using namespace bebra;

namespace craft {

objects::chunk genChunk() {
    objects::chunk chunk;

    // LOAD BLOCKS!
    /// Load textures
    objects::ObjectTexture furnaceTexture {{
        path + "furnace_front_on.png",
        path + "furnace_side.png",
        path + "furnace_side.png",
        path + "furnace_side.png",
        path + "furnace_top.png",
        path + "furnace_top.png"
    }};
    
    objects::ObjectTexture stoneTexture {
        path + "stone.png",
    };

    objects::ObjectTexture dirtTexture {
        path + "dirt.png"
    };

    objects::ObjectTexture grassTexture {{
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        path + "grass_block_top.png",
        path + "dirt.png"
    }};

    objects::ObjectTexture glass_grayTexture {
        path + "gray_stained_glass.png"
    };
    
    objects::ObjectTexture glassTexture {
        path + "glass.png"
    };

    objects::ObjectTexture leaves_oakTexture {
        path + "oak_leaves.png"
    };

    objects::ObjectTexture tallgrassTexture {
        path + "grass.png", 4
    };

    objects::ObjectTexture stonebrickTexture {
        path + "stonebrick.png"
    };

    objects::ObjectTexture planks_big_oakTexture {
        path + "dark_oak_planks.png"
    };

    objects::ObjectTexture big_oakTexture {{
        path + "dark_oak_log.png",
        path + "dark_oak_log.png",
        path + "dark_oak_log.png",
        path + "dark_oak_log.png",
        path + "dark_oak_log_top.png",
        path + "dark_oak_log_top.png"
    }};

    objects::ObjectTexture planks_birchTexture {
        path + "birch_planks.png"
    };

    objects::ObjectTexture oakTexture {{
        path + "oak_log.png",
        path + "oak_log.png",
        path + "oak_log.png",
        path + "oak_log.png",
        path + "oak_log_top.png",
        path + "oak_log_top.png"
    }};

    objects::ObjectTexture jukeboxTexture {{
        path + "jukebox_side.png",
        path + "jukebox_side.png",
        path + "jukebox_side.png",
        path + "jukebox_side.png",
        path + "jukebox_top.png",
        path + "jukebox_side.png"
    }};

    objects::ObjectTexture glowstoneTexture {
        path + "glowstone.png"
    };

    objects::ObjectTexture gravelTexture {
        path + "gravel.png"
    };

    objects::ObjectTexture crafting_tableTexture {{
        path + "crafting_table_front.png",
        path + "crafting_table_side.png",
        path + "crafting_table_side.png",
        path + "crafting_table_side.png",
        path + "crafting_table_top.png",
        path + "birch_planks.png"
    }};

    objects::ObjectTexture quartz_block_chiseledTexture {
        path + "chiseled_quartz_block_top.png"
    };

    objects::ObjectTexture waterTexture {
        path + "water_still.png"
    };

    objects::ObjectTexture iron_oreTexture { path + "iron_ore.png" };
    objects::ObjectTexture gold_oreTexture { path + "gold_ore.png" };
    objects::ObjectTexture diamond_oreTexture { path + "diamond_ore.png" };
    objects::ObjectTexture coal_oreTexture { path + "coal_ore.png" };

    /// Create blocks object
    objects::Block* furnaceBlock1 = new objects::Block { furnaceTexture, -90.0f };
    objects::Block* furnaceBlock2 = new objects::Block { furnaceTexture, 180.0f };
    objects::Block* stoneBlock = new objects::Block { stoneTexture };
    objects::Block* dirtBlock = new objects::Block { dirtTexture };
    objects::Block* grassBlock = new objects::Block { grassTexture };
    objects::Block* oakBlock = new objects::Block { oakTexture };
    objects::Block* planks_birchBlock = new objects::Block { planks_birchTexture };
    objects::Block* big_oakBlock = new objects::Block { big_oakTexture };
    objects::Block* planks_big_oakBlock = new objects::Block { planks_big_oakTexture };
    objects::Block* leaves_oakBlock = new objects::Block { leaves_oakTexture };
    objects::Glass* glass_grayBlock = new objects::Glass { glass_grayTexture };
    objects::Block* jukeboxBlock = new objects::Block { jukeboxTexture };
    objects::Glass* glassBlock = new objects::Glass { glassTexture };
    objects::Block* glowstoneBlock = new objects::Block { glowstoneTexture };
    objects::Block* gravelBlock = new objects::Block { gravelTexture };
    objects::Block* crafting_tableBlock = new objects::Block { crafting_tableTexture };
    objects::Plant* tallgrassBlock = new objects::Plant { tallgrassTexture };
    objects::Fluid* waterBlock = new objects::Fluid { waterTexture };
    objects::Block* quartz_block_chiseledBlock = new objects::Block { quartz_block_chiseledTexture };
    objects::Block* iron_oreBlock = new objects::Block { iron_oreTexture };
    objects::Block* diamond_oreBlock = new objects::Block { diamond_oreTexture };
    objects::Block* coal_oreBlock = new objects::Block { coal_oreTexture };
    objects::Block* gold_oreBlock = new objects::Block { gold_oreTexture };

    static const std::array<objects::Object*, 24> b {
        new objects::Object {}, stoneBlock, grassBlock, dirtBlock, leaves_oakBlock, oakBlock, planks_birchBlock, big_oakBlock, planks_big_oakBlock, glassBlock,
        glowstoneBlock, glass_grayBlock, gravelBlock, crafting_tableBlock, furnaceBlock1, jukeboxBlock, iron_oreBlock, coal_oreBlock, gold_oreBlock, diamond_oreBlock,
        tallgrassBlock, waterBlock, quartz_block_chiseledBlock, furnaceBlock2
    };

    {// CREATE LAYERS!
        objects::chunkLayer layer;
        using row = objects::chunkRow;

        // 1
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[16],b[1],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[18],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 2
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[19],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[17],b[1],b[1],b[19],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[18],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 3
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[17],b[1],b[1],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[0],b[0],b[1],b[1],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[1],b[1],b[17],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[16],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[1],b[16],b[16],b[1],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 4
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[1],b[1],b[19],b[19],b[1],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[18],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[18],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0] },
            row { b[0],b[0],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0] },
            row { b[0],b[0],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0] },
            row { b[0],b[0],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[17],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[16],b[1],b[1],b[1],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[1],b[16],b[1],b[1],b[1],b[1],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 5
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[0],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 6
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0] },
            row { b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0] },
            row { b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[3],b[3],b[3],b[3],b[3],b[3],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 7
        layer = {
            row { b[0],b[0],b[0],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[0],b[0],b[0] },
            row { b[0],b[2],b[2],b[2],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[2],b[2],b[0] },
            row { b[2],b[2],b[2],b[2],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[8],b[6],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[12],b[12],b[12],b[2],b[2],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[2],b[21],b[21],b[21],b[21],b[2],b[2],b[2],b[2],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[21],b[21],b[21],b[21],b[21],b[21],b[2],b[2],b[2],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[21],b[21],b[21],b[21],b[21],b[21],b[2],b[2],b[2],b[2],b[2],b[2] },
            row { b[2],b[2],b[2],b[2],b[21],b[21],b[21],b[21],b[21],b[21],b[2],b[2],b[2],b[2],b[2],b[2] },
            row { b[0],b[2],b[2],b[2],b[2],b[2],b[21],b[21],b[21],b[2],b[2],b[2],b[2],b[2],b[2],b[0] },
            row { b[0],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[0],b[0] },
            row { b[0],b[0],b[0],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[2],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 8 House
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[6],b[6],b[6],b[6],b[6],b[6],b[7],b[0],b[0],b[20] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[23],b[6],b[0],b[0],b[0] },
            row { b[0],b[20],b[0],b[0],b[6],b[13],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[20],b[0],b[6],b[14],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[15],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[6],b[6],b[6],b[0],b[6],b[6],b[7],b[0],b[0],b[0] },
            row { b[0],b[20],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[20] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[20],b[20],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[20],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[20],b[0],b[0],b[0],b[0],b[0],b[0],b[20],b[0],b[5],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[20],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 9
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[6],b[6],b[6],b[6],b[6],b[6],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[11],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[11],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[11],b[11],b[6],b[0],b[6],b[6],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[5],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 10
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[6],b[6],b[6],b[6],b[6],b[6],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[11],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[11],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[6],b[11],b[11],b[6],b[6],b[6],b[6],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[5],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 11
        layer = {
            row { b[0],b[0],b[0],b[0],b[7],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[22],b[22],b[22],b[22],b[22],b[22],b[22],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[22],b[10],b[22],b[22],b[22],b[10],b[22],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[22],b[10],b[22],b[22],b[22],b[10],b[22],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[22],b[22],b[22],b[22],b[22],b[22],b[0],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[5],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[4],b[4],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 12
        layer = {
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[5],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 13
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[9],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[9],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[9],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[9],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[4],b[4],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[4],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },

        };
        chunk.push_back(layer);

        // 14
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[6],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[8],b[8],b[8],b[8],b[8],b[8],b[8],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);

        // 15
        layer = {
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[7],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
            row { b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0],b[0] },
        };
        chunk.push_back(layer);
    }

    return chunk;

}

} // namespace craft