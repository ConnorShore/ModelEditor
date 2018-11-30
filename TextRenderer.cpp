#include "TextRenderer.h"
#include <stdio.h>

TextRenderer::TextRenderer() : _vaoID(0), _vboID(0)
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::init()
{
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
        printf("Failed to initialize FreeType Library\n");
    
    FT_Face face;
    if(FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
        printf("Failed to load font\n");
    
    FT_Set_Pixel_Sizes(face, 0, 18);    //18 pt font I believe
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte i = 0; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER))
            printf("Failed to load glyph: %d\n", (int)i);
        
        GLuint texID;
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows,
                     0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
                     
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character;
        character.textureID = texID;
        character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.advance = face->glyph->advance.x;
        _characters.insert(std::pair<GLchar, Character>(i, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::renderText(ShaderProgram& shader, std::string text, float x, float y, float size, glm::vec4 color)
{
    
}