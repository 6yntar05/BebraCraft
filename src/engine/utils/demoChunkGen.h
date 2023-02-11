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
        GLuint alpha;
        bebra::graphics::loadTexture(&alpha, "textures/blocks/alpha.png", GL_RGBA);

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

        GLuint log_oak, log_oak_top;
        bebra::graphics::loadTexture(&log_oak, "textures/blocks/log_oak.png", GL_RGBA);
        bebra::graphics::loadTexture(&log_oak_top, "textures/blocks/log_oak_top.png", GL_RGBA);
        bebra::objects::blockTexture oakTexture { log_oak, log_oak, log_oak_top, log_oak_top, log_oak, log_oak };

        GLuint leaves_oak;
        bebra::graphics::loadTexture(&leaves_oak, "textures/blocks/leaves_oak.png", GL_RGBA);
        bebra::objects::blockTexture leaves_oakTexture { leaves_oak };

        GLuint tallgrass;
        bebra::graphics::loadTexture(&tallgrass, "textures/blocks/tallgrass.png", GL_RGBA);
        bebra::objects::blockTexture tallgrassTexture { tallgrass, tallgrass, alpha, alpha, tallgrass, tallgrass };

        /// Create blocks object
        objects::block* furnaceBlock = new objects::block { furnaceTexture };
        objects::block* stoneBlock = new objects::block { stoneTexture }; auto b0 = stoneBlock;
        objects::block* dirtBlock = new objects::block { dirtTexture }; auto b1 = dirtBlock;
        objects::block* grassBlock = new objects::block { grassTexture };
        objects::block* oakBlock = new objects::block { oakTexture };
        objects::block* leaves_oakBlock = new objects::block { leaves_oakTexture };
        objects::block* glass_light_blueBlock = new objects::block { glass_light_blueTexture };
        objects::block* tallgrassBlock = new objects::block { tallgrassTexture , 45.0 };
        //tallgrassBlock->rotate = 45.0;

        {// CREATE LAYERS!
            objects::chunkLayer layer;
            /// 0-5
            for (int i = 0; i < 5; i++) {
                layer = {};
                for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
                    objects::chunkRow row;
                    for (int y = 0; y < 16; y++)
                        if ((y==0) or (y==15) or (rowsCount==0)or(rowsCount==15))
                            row[y] = stoneBlock;
                        else 
                            row[y] = &objects::air;
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
                        row[y] = leaves_oakBlock;

                    else
                        row[y] = &objects::air;

                layer[rowsCount] = row;
            }
            chunk.push_back(layer);
            /// 8
            layer = {};
            for (int rowsCount = 0; rowsCount < 16; rowsCount++) {
                objects::chunkRow row;
                for (int y = 0; y < 16; y++)
                    if ((rowsCount == 5) && (y == 5))
                        row[y] = oakBlock;

                    else if ((rowsCount == 9) && (y == 9))
                        row[y] = tallgrassBlock;

                    else
                        row[y] = &objects::air;

                layer[rowsCount] = row;
            }
            chunk.push_back(layer);
        }
        
        return chunk;
    }
}
}