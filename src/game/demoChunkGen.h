#pragma once

#include <array>
#include <vector>

#include "engine/objects/block.h"
#include "engine/objects/plant.h"
#include "engine/objects/object.h"
#include "engine/world/chunk.h"
#include "engine/graphics/textures.h"


namespace bebra {
namespace utils {

    objects::chunk genChunk() {
        objects::chunk chunk;

        // LOAD BLOCKS!
        /// Load textures
        GLuint alpha;
        bebra::graphics::loadTexture(&alpha, "textures/blocks/alpha.png");

        GLuint furnace_top, furnace_side, furnace_front_on;
        bebra::graphics::loadTexture(&furnace_top, "textures/blocks/furnace_top.png");
        bebra::graphics::loadTexture(&furnace_side, "textures/blocks/furnace_side.png");
        bebra::graphics::loadTexture(&furnace_front_on, "textures/blocks/furnace_front_on.png");
        bebra::objects::blockTexture furnaceTexture
            { furnace_front_on, furnace_side, furnace_side, furnace_side, furnace_top, furnace_top };
        
        GLuint stone;
        bebra::graphics::loadTexture(&stone, "textures/blocks/stone.png");
        bebra::objects::blockTexture stoneTexture { stone };

        GLuint dirt;
        bebra::graphics::loadTexture(&dirt, "textures/blocks/dirt.png");
        bebra::objects::blockTexture dirtTexture { dirt };
        
        GLuint grass_side, grass_top;
        bebra::graphics::loadTexture(&grass_side, "textures/blocks/grass_side.png");
        bebra::graphics::loadTexture(&grass_top, "textures/blocks/grass_top.png");
        bebra::objects::blockTexture grassTexture { grass_side, grass_side, grass_side, grass_side, grass_top, dirt };

        GLuint glass_gray;
        bebra::graphics::loadTexture(&glass_gray, "textures/blocks/glass_gray.png");
        bebra::objects::blockTexture glass_grayTexture { glass_gray };
        
        GLuint glass;
        bebra::graphics::loadTexture(&glass, "textures/blocks/glass.png");
        bebra::objects::blockTexture glassTexture { glass };

        GLuint leaves_oak;
        bebra::graphics::loadTexture(&leaves_oak, "textures/blocks/leaves_oak.png");
        bebra::objects::blockTexture leaves_oakTexture { leaves_oak };

        GLuint tallgrass;
        bebra::graphics::loadTexture(&tallgrass, "textures/blocks/tallgrass.png");
        bebra::objects::plantTexture tallgrassTexture { tallgrass };

        GLuint stonebrick;
        bebra::graphics::loadTexture(&stonebrick, "textures/blocks/stonebrick.png");
        bebra::objects::blockTexture stonebrickTexture { stonebrick };

        GLuint planks_big_oak;
        bebra::graphics::loadTexture(&planks_big_oak, "textures/blocks/planks_big_oak.png");
        bebra::objects::blockTexture planks_big_oakTexture { planks_big_oak };

        GLuint log_big_oak, log_big_oak_top;
        bebra::graphics::loadTexture(&log_big_oak, "textures/blocks/log_big_oak.png");
        bebra::graphics::loadTexture(&log_big_oak_top, "textures/blocks/log_big_oak_top.png");
        bebra::objects::blockTexture big_oakTexture { log_big_oak, log_big_oak, log_big_oak, log_big_oak, log_big_oak_top, log_big_oak_top };

        GLuint planks_birch;
        bebra::graphics::loadTexture(&planks_birch, "textures/blocks/planks_birch.png");
        bebra::objects::blockTexture planks_birchTexture { planks_birch };

        GLuint log_oak, log_oak_top;
        bebra::graphics::loadTexture(&log_oak, "textures/blocks/log_oak.png");
        bebra::graphics::loadTexture(&log_oak_top, "textures/blocks/log_oak_top.png");
        bebra::objects::blockTexture oakTexture { log_oak, log_oak, log_oak, log_oak, log_oak_top, log_oak_top };
 
        GLuint jukebox_side, jukebox_top;
        bebra::graphics::loadTexture(&jukebox_side, "textures/blocks/jukebox_side.png");
        bebra::graphics::loadTexture(&jukebox_top, "textures/blocks/jukebox_top.png");
        bebra::objects::blockTexture jukeboxTexture { jukebox_side, jukebox_side, jukebox_side, jukebox_side, jukebox_top, jukebox_side };

        GLuint iron_ore, gold_ore, diamond_ore, coal_ore;
        bebra::graphics::loadTexture(&iron_ore, "textures/blocks/iron_ore.png");
        bebra::graphics::loadTexture(&gold_ore, "textures/blocks/gold_ore.png");
        bebra::graphics::loadTexture(&diamond_ore, "textures/blocks/diamond_ore.png");
        bebra::graphics::loadTexture(&coal_ore, "textures/blocks/coal_ore.png");
        bebra::objects::blockTexture iron_oreTexture { iron_ore };
        bebra::objects::blockTexture gold_oreTexture { gold_ore };
        bebra::objects::blockTexture diamond_oreTexture { diamond_ore };
        bebra::objects::blockTexture coal_oreTexture { coal_ore };

        GLuint glowstone;
        bebra::graphics::loadTexture(&glowstone, "textures/blocks/glowstone.png");
        bebra::objects::blockTexture glowstoneTexture { glowstone };

        GLuint gravel;
        bebra::graphics::loadTexture(&gravel, "textures/blocks/gravel.png");
        bebra::objects::blockTexture gravelTexture { gravel };

        GLuint door_wood_upper, door_wood_lower;
        bebra::graphics::loadTexture(&door_wood_upper, "textures/blocks/door_wood_uppe.png");
        bebra::graphics::loadTexture(&door_wood_lower, "textures/blocks/door_wood_lower.png");
        //bebra::objects::blockTexture jukeboxTexture { log_oak, log_oak, log_oak_top, log_oak_top, log_oak, log_oak };


        GLuint crafting_table_front, crafting_table_side, crafting_table_top;
        bebra::graphics::loadTexture(&crafting_table_front, "textures/blocks/crafting_table_front.png");
        bebra::graphics::loadTexture(&crafting_table_side, "textures/blocks/crafting_table_side.png");
        bebra::graphics::loadTexture(&crafting_table_top, "textures/blocks/crafting_table_top.png");
        bebra::objects::blockTexture crafting_tableTexture { crafting_table_front, crafting_table_side, crafting_table_side, crafting_table_side, crafting_table_top, planks_birch };

        GLuint quartz_block_chiseled;
        bebra::graphics::loadTexture(&quartz_block_chiseled, "textures/blocks/quartz_block_chiseled.png");
        bebra::objects::blockTexture quartz_block_chiseledTexture { quartz_block_chiseled };

        GLuint water;
        bebra::graphics::loadTexture(&water, "textures/blocks/water.png");
        bebra::objects::blockTexture waterTexture { water };

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
        objects::block* glass_grayBlock = new objects::block { glass_grayTexture };
        objects::block* jukeboxBlock = new objects::block { jukeboxTexture };
        objects::block* iron_oreBlock = new objects::block { iron_ore };
        objects::block* diamond_oreBlock = new objects::block { diamond_oreTexture };
        objects::block* coal_oreBlock = new objects::block { coal_oreTexture };
        objects::block* gold_oreBlock = new objects::block { gold_oreTexture };
        objects::block* glassBlock = new objects::block { glassTexture };
        objects::block* glowstoneBlock = new objects::block { glowstoneTexture };
        objects::block* gravelBlock = new objects::block { gravelTexture };
        objects::block* crafting_tableBlock = new objects::block { crafting_tableTexture };
        objects::plant* tallgrassBlock = new objects::plant { tallgrassTexture };
        objects::block* waterBlock = new objects::block { waterTexture };
        objects::block* quartz_block_chiseledBlock = new objects::block { quartz_block_chiseledTexture };

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
}