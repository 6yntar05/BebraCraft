#pragma once

#include <array>
#include <vector>

#include "engine/objects/block.h"
#include "engine/objects/fluid.h"
#include "engine/objects/chunk.h"
#include "engine/graphics/textures.h"


namespace bebra {
namespace utils {

    objects::chunk genChunk() {
        objects::chunk chunk;

        // LOAD BLOCKS!
        /// Load textures
        GLuint furnace_top, furnace_side, furnace_front_on;
        bebra::graphics::loadTexture(&furnace_top, "textures/blocks/furnace_top.png", GL_RGBA);
        bebra::graphics::loadTexture(&furnace_side, "textures/blocks/furnace_side.png", GL_RGBA);
        bebra::graphics::loadTexture(&furnace_front_on, "textures/blocks/furnace_front_on.png", GL_RGBA);
        bebra::objects::blockTexture furnaceTexture
            { furnace_front_on, furnace_side, furnace_top, furnace_top, furnace_side, furnace_side };
        
        GLuint stone;
        bebra::graphics::loadTexture(&stone, "textures/blocks/stone.png", GL_RGBA);
        bebra::objects::blockTexture stoneTexture { stone };

        GLuint dirt;
        bebra::graphics::loadTexture(&dirt, "textures/blocks/dirt.png", GL_RGBA);
        bebra::objects::blockTexture dirtTexture { dirt };
        
        GLuint grass_side, grass_top;
        bebra::graphics::loadTexture(&grass_side, "textures/blocks/grass_side.png", GL_RGBA);
        bebra::graphics::loadTexture(&grass_top, "textures/blocks/grass_top.png", GL_RGBA);
        bebra::objects::blockTexture grassTexture { grass_side, grass_side, grass_top, dirt, grass_side, grass_side };

        GLuint glass_light_blue;
        bebra::graphics::loadTexture(&glass_light_blue, "textures/blocks/glass_light_blue.png", GL_RGBA);
        bebra::objects::blockTexture glass_light_blueTexture { glass_light_blue };

        /// Create blocks object
        objects::block furnaceBlock { furnaceTexture };
        objects::block stoneBlock { stoneTexture };
        objects::block dirtBlock { dirtTexture };
        objects::block grassBlock { grassTexture };
        objects::block glass_light_blueBlock { glass_light_blueTexture };

        // objects::fluid waterFluid { {}, furnaceTexture };

        // CREATE LAYERS!
        objects::chunkLayer layer;
        /// 0-5
        for (int i = 0; i < 5; i++) {
            layer = {};
            for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
                objects::chunkRow row;
                for (int y = 0; y < 16; y++)
                    if (y%2==0)
                        row[y] = stoneBlock;
                    else 
                        row[y] = dirtBlock;
                layer[rowsCount] = row;
            }
            chunk.push_back(layer);
        }
        /// 6
        layer = {};
        for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
            objects::chunkRow row;
            for (int y = 0; y < 16; y++)
               row[y] = grassBlock;
            layer[rowsCount] = row;
        }
        chunk.push_back(layer);
        /// 7
        layer = {};
        for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
            objects::chunkRow row;
            for (int y = 0; y < 16; y++)
                if ((rowsCount == 2) && (y == 8))
                    row[y] = furnaceBlock;
                
                //else if ((rowsCount == 3) && (y == 9)) row[y] = *dynamic_cast<objects::block*>(&waterFluid);

                else if (((rowsCount > 4) && (rowsCount < 8)) && ((y > 3) && (y < 6)))
                    row[y] = glass_light_blueBlock;

                else
                    row[y] = objects::air;

            layer[rowsCount] = row;
        }
        chunk.push_back(layer);
        /// 8
        layer = {};
        for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
            objects::chunkRow row;
            for (int y = 0; y < 16; y++)
                if ((rowsCount == 5) && (y == 5))
                    row[y] = glass_light_blueBlock;

                else
                    row[y] = objects::air;

            layer[rowsCount] = row;
        }
        chunk.push_back(layer);

        return chunk;
    }
}
}