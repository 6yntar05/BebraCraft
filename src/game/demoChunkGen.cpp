#include <array>
#include <vector>

#include "game/demoChunkGen.h"

#include "engine/objects/objects.h"
#include "engine/graphics/textures.h"

using namespace bebra;

namespace craft {

    objects::chunk genChunk() {
        objects::chunk chunk;

        // LOAD BLOCKS!
        /// Load textures
        objects::objectTexture furnaceTexture {{
            "textures/blocks/furnace_front_on.png",
            "textures/blocks/furnace_side.png",
            "textures/blocks/furnace_side.png",
            "textures/blocks/furnace_side.png",
            "textures/blocks/furnace_top.png",
            "textures/blocks/furnace_top.png"
        }};
        
        objects::objectTexture stoneTexture {
            "textures/blocks/stone.png",
        };

        objects::objectTexture dirtTexture {
            "textures/blocks/dirt.png"
        };

        objects::objectTexture grassTexture {{
            "textures/blocks/grass_side.png",
            "textures/blocks/grass_side.png",
            "textures/blocks/grass_side.png",
            "textures/blocks/grass_side.png",
            "textures/blocks/grass_top.png",
            "textures/blocks/dirt.png"
        }};

        objects::objectTexture glass_grayTexture {
            "textures/blocks/glass_gray.png"
        };
        
        objects::objectTexture glassTexture {
            "textures/blocks/glass.png"
        };

        objects::objectTexture leaves_oakTexture {
            "textures/blocks/leaves_oak.png"
        };

        objects::objectTexture tallgrassTexture {
            "textures/blocks/tallgrass.png", 4
        };

        objects::objectTexture stonebrickTexture {
            "textures/blocks/stonebrick.png"
        };

        objects::objectTexture planks_big_oakTexture {
            "textures/blocks/planks_big_oak.png"
        };

        objects::objectTexture big_oakTexture {{
            "textures/blocks/log_big_oak.png",
            "textures/blocks/log_big_oak.png",
            "textures/blocks/log_big_oak.png",
            "textures/blocks/log_big_oak.png",
            "textures/blocks/log_big_oak_top.png",
            "textures/blocks/log_big_oak_top.png"
        }};

        objects::objectTexture planks_birchTexture {
            "textures/blocks/planks_birch.png"
        };

        objects::objectTexture oakTexture {{
            "textures/blocks/log_oak.png",
            "textures/blocks/log_oak.png",
            "textures/blocks/log_oak.png",
            "textures/blocks/log_oak.png",
            "textures/blocks/log_oak_top.png",
            "textures/blocks/log_oak_top.png"
        }};

        objects::objectTexture jukeboxTexture {{
            "textures/blocks/jukebox_side.png",
            "textures/blocks/jukebox_side.png",
            "textures/blocks/jukebox_side.png",
            "textures/blocks/jukebox_side.png",
            "textures/blocks/jukebox_top.png",
            "textures/blocks/jukebox_side.png"
        }};

        objects::objectTexture glowstoneTexture {
            "textures/blocks/glowstone.png"
        };

        objects::objectTexture gravelTexture {
            "textures/blocks/gravel.png"
        };

        objects::objectTexture crafting_tableTexture {{
            "textures/blocks/crafting_table_front.png",
            "textures/blocks/crafting_table_side.png",
            "textures/blocks/crafting_table_side.png",
            "textures/blocks/crafting_table_side.png",
            "textures/blocks/crafting_table_top.png",
            "textures/blocks/planks_birch.png"
        }};

        objects::objectTexture quartz_block_chiseledTexture {
            "textures/blocks/quartz_block_chiseled.png"
        };

        objects::objectTexture waterTexture {
            "textures/blocks/water.png"
        };

        objects::objectTexture iron_oreTexture { "textures/blocks/iron_ore.png" };
        objects::objectTexture gold_oreTexture { "textures/blocks/gold_ore.png" };
        objects::objectTexture diamond_oreTexture { "textures/blocks/diamond_ore.png" };
        objects::objectTexture coal_oreTexture { "textures/blocks/coal_ore.png" };

        /// Create blocks object
        objects::block* furnaceBlock1 = new objects::block { furnaceTexture, -90.0f };
        objects::block* furnaceBlock2 = new objects::block { furnaceTexture, 180.0f };
        objects::block* stoneBlock = new objects::block { stoneTexture };
        objects::block* dirtBlock = new objects::block { dirtTexture };
        objects::block* grassBlock = new objects::block { grassTexture };
        objects::block* oakBlock = new objects::block { oakTexture };
        objects::block* planks_birchBlock = new objects::block { planks_birchTexture };
        objects::block* big_oakBlock = new objects::block { big_oakTexture };
        objects::block* planks_big_oakBlock = new objects::block { planks_big_oakTexture };
        objects::block* leaves_oakBlock = new objects::block { leaves_oakTexture };
        objects::glass* glass_grayBlock = new objects::glass { glass_grayTexture };
        objects::block* jukeboxBlock = new objects::block { jukeboxTexture };
        objects::glass* glassBlock = new objects::glass { glassTexture };
        objects::block* glowstoneBlock = new objects::block { glowstoneTexture };
        objects::block* gravelBlock = new objects::block { gravelTexture };
        objects::block* crafting_tableBlock = new objects::block { crafting_tableTexture };
        objects::plant* tallgrassBlock = new objects::plant { tallgrassTexture };
        objects::fluid* waterBlock = new objects::fluid { waterTexture };
        objects::block* quartz_block_chiseledBlock = new objects::block { quartz_block_chiseledTexture };
        objects::block* iron_oreBlock = new objects::block { iron_oreTexture };
        objects::block* diamond_oreBlock = new objects::block { diamond_oreTexture };
        objects::block* coal_oreBlock = new objects::block { coal_oreTexture };
        objects::block* gold_oreBlock = new objects::block { gold_oreTexture };

        static const std::array<objects::object*, 24> b {
            new objects::object {}, stoneBlock, grassBlock, dirtBlock, leaves_oakBlock, oakBlock, planks_birchBlock, big_oakBlock, planks_big_oakBlock, glassBlock,
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

}