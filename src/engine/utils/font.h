#pragma once
#include "engine/graphics/shaders.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace bebra::utils {

struct Character {
	unsigned int TextureID;	// Glyph texture
	glm::ivec2 Size;		// размер глифа
	glm::ivec2 Bearing;		// Offset from center to top left corner
	unsigned int Advance;	// смещение до следующего глифа
};
static std::map<char, Character> Characters;

class Font {
  private:
  	graphics::ShaderProgram shader;
    uint VAO, VBO;

  public:
	const uint width;
	const uint height;

    void render(std::string text, glm::mat4& projection, float x, float y, glm::vec3 color = {1.0, 1.0, 1.0}, float scale = 1.0) {
		// Load shaders & projection
        shader.use();
        glUniform3f(glGetUniformLocation(shader.program, "textColor"), color.x, color.y, color.z);
        glUniformMatrix4fv(glGetUniformLocation(shader.program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
    
        // Iterate a string
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            bebra::utils::Character ch = bebra::utils::Characters[*c];
            // View texture
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);

            // Update VBO & render glyph
            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

			float vertices[6][4] = {
                { xpos, ypos + h, 0.0f, 0.0f },            
                { xpos, ypos, 0.0f, 1.0f },
                { xpos + w, ypos, 1.0f, 1.0f },
    
                { xpos, ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos, 1.0f, 1.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f }           
            };

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
    
            // Set offset for next char
            x += (ch.Advance >> 6) * scale;
        }

		// Unbind
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Font(const std::string path, const graphics::ShaderProgram shader, const uint width, const uint height = 0)
	: shader(shader), width(width), height(height) {
		FT_Library ft;
        if (FT_Init_FreeType(&ft))
            std::cerr << "ERROR::FREETYPE::INIT" << std::endl;

		FT_Face face;
        auto error = FT_New_Face(ft, path.c_str(), 0, &face);
        if ( error == FT_Err_Unknown_File_Format )
            std::cerr << "ERROR::FREETYPE: Unknown file format" << std::endl;
        else if (error)
            std::cerr << "ERROR::FREETYPE: " << error << std::endl;

        FT_Set_Pixel_Sizes(face, height, width);
        //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        for (unsigned int c = 0; c < 256; c++) {
            // Loading glyphs
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
                continue;
            }
        
            // Gen texture
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
        
            // Save symbol
            bebra::utils::Character character = {
                texture, 
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            bebra::utils::Characters.insert(std::pair<char, bebra::utils::Character>(c, character));
        }
		// Close FT
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

		// Gen VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    ~Font() {
    }
};

} // namespace bebra::utils
