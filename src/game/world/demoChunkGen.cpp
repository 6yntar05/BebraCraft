#include <array>
#include <vector>
#include "engine/objects/base.h"
#include "game/world/demoChunkGen.h"
#include "engine/objects/objects.h"
#include "engine/graphics/textures.h"
#include <engine/utils/textures.h>

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

    bebra::graphics::Texture grassC {path + "grass_block_top.png"};
    bebra::utils::colorize(grassC, {0.4, 1.0, 0.4}, {0.05, 0.09, 0.05});
    objects::ObjectTexture grassTexture {{
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        path + "grass_block_side.png",
        grassC,
        path + "dirt.png"
    }};

    objects::ObjectTexture glass_grayTexture {
        path + "gray_stained_glass.png"
    };
    
    objects::ObjectTexture glassTexture {
        path + "glass.png"
    };

    bebra::graphics::Texture leavesC {path + "oak_leaves.png"};
    bebra::utils::colorize(leavesC, {0.3, 1.0, 0.3});
    objects::ObjectTexture leaves_oakTexture {
        {leavesC, leavesC, leavesC, leavesC, leavesC, leavesC}
    };

    bebra::graphics::Texture tgrassC {path + "grass.png"};
    bebra::utils::colorize(tgrassC, {0.3, 1.0, 0.3}, {0.2, 0.2, 0.2});
    objects::ObjectTexture tallgrassTexture {
        {tgrassC, tgrassC, tgrassC, tgrassC}
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

    bebra::graphics::Texture testTex {path + "water_still.png"};
    bebra::utils::colorize(testTex, {0.35, 0.4, 1.0});
    objects::ObjectTexture waterTexture {
        {testTex, testTex, testTex, testTex, testTex, testTex}
    };

    objects::ObjectTexture iron_oreTexture { path + "iron_ore.png" };
    objects::ObjectTexture gold_oreTexture { path + "gold_ore.png" };
    objects::ObjectTexture diamond_oreTexture { path + "diamond_ore.png" };
    objects::ObjectTexture coal_oreTexture { path + "coal_ore.png" };

    /// Create blocks object
    objects::Object* furnaceBlock1 = new objects::Block { furnaceTexture, -90.0f };
    objects::Object* furnaceBlock2 = new objects::Block { furnaceTexture, 180.0f };
    objects::Object* stoneBlock = new objects::Block { stoneTexture };
    objects::Object* dirtBlock = new objects::Block { dirtTexture };
    objects::Object* grassBlock = new objects::Block { grassTexture };
    objects::Object* oakBlock = new objects::Block { oakTexture };
    objects::Object* planks_birchBlock = new objects::Block { planks_birchTexture };
    objects::Object* big_oakBlock = new objects::Block { big_oakTexture };
    objects::Object* planks_big_oakBlock = new objects::Block { planks_big_oakTexture };
    objects::Object* leaves_oakBlock = new objects::Block { leaves_oakTexture };
        leaves_oakBlock->id = bebra::objects::etransparent;
    objects::Object* glass_grayBlock = new objects::Block { glass_grayTexture };
        glass_grayBlock->id = bebra::objects::esemitransparent;
    objects::Object* jukeboxBlock = new objects::Block { jukeboxTexture };
    objects::Object* glassBlock = new objects::Block { glassTexture };
        glassBlock->id = bebra::objects::etransparent;
    objects::Object* glowstoneBlock = new objects::Block { glowstoneTexture };
    objects::Object* gravelBlock = new objects::Block { gravelTexture };
    objects::Object* crafting_tableBlock = new objects::Block { crafting_tableTexture };
    objects::Object* tallgrassBlock = new objects::Plant { tallgrassTexture };
    objects::Object* waterBlock = new objects::Fluid { waterTexture };
    objects::Object* quartz_block_chiseledBlock = new objects::Block { quartz_block_chiseledTexture };
    objects::Object* iron_oreBlock = new objects::Block { iron_oreTexture };
    objects::Object* diamond_oreBlock = new objects::Block { diamond_oreTexture };
    objects::Object* coal_oreBlock = new objects::Block { coal_oreTexture };
    objects::Object* gold_oreBlock = new objects::Block { gold_oreTexture };

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