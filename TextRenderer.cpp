#include "TextRenderer.h"
#include <stdio.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "Math.h"

TextRenderer::TextRenderer() : _vaoID(0), _vboID(0)
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::init(TextShader* shader, int width, int height)
{
    // shader->start();

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
        printf("Failed to initialize FreeType Library\n");
    
    FT_Face face;
    if(FT_New_Face(ft, "Fonts/arial.ttf", 0, &face))
        printf("Failed to load font\n");
    
    FT_Set_Pixel_Sizes(face, 0, 42);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte i = 0; i < 128; i++) {
        if(FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            printf("Failed to load glyph: %d\n", (int)i);
            continue;
        }
        
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
        // character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        // character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        // character.advance.x = face->glyph->advance.x;
        // character.advance.y = face->glyph->advance.y;
        character.size = glm::ivec2(face->glyph->metrics.width>>6, face->glyph->metrics.height>>6);
        character.bearing = glm::ivec2(face->glyph->metrics.horiBearingX>>6, face->glyph->metrics.vertBearingY>>6);
        character.advance.x = face->glyph->metrics.horiAdvance>>6;
        character.advance.y = face->glyph->metrics.vertAdvance>>6;
        _characters.insert(std::pair<GLchar, Character>(i, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    //Create VAO and VBO
    glGenVertexArrays(1, &_vaoID);
    glGenBuffers(1, &_vboID);

    glBindVertexArray(_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 10, &vertices[0], GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::prepare(TextShader* shader, int width, int height)
{
    shader->start();
    // shader->loadGlyph();
}

void TextRenderer::end(TextShader* shader)
{
    shader->stop();
}

void TextRenderer::renderText(TextShader* shader, std::string text, float x, float y, float size, glm::vec3 color)
{
    glDisable(GL_DEPTH_TEST);
    shader->start();
    shader->getUniformLocations();
    glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(1600), 0.0f, static_cast<GLfloat>(900));
    shader->loadProjectionMatrix(proj);
    shader->loadColor(color);
    shader->loadGlyph();

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vaoID);

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = _characters[*c];
        printf("Char: %c; bearing: %d; size: %d; advance: %d\n", *c, ch.bearing.y, ch.size.y, ch.advance.y);
        float xpos = x + ch.bearing.x * size;
        float ypos = y + ((ch.size.y - ch.bearing.y)/2.0f) * size;

        float w = ch.size.x * size;
        float h = ch.size.y * size;

        glm::mat4 transform = Math::createTransformationMatrix(glm::vec2(xpos+w/2,ypos+h/2), glm::vec2(0.0f), glm::vec2(w,h));
        shader->loadTransformationMatrix(transform);

        // float vertices[6][4] = {
        //     { xpos, ypos + h, 0.0f, 0.0f},
        //     { xpos, ypos, 0.0f, 1.0f},
        //     { xpos + w, ypos, 1.0f, 1.0f},

        //     { xpos, ypos + h, 0.0f, 0.0f},
        //     { xpos + w, ypos, 1.0f, 1.0f},
        //     { xpos + w, ypos + h, 1.0f, 0.0f},
        // };

        // GLfloat vertices[4][4] = {
        //     {xpos, -ypos, 0.0f, 0.0f},
        //     {xpos + w, -ypos, 1.0f, 0.0f},
        //     {xpos, -ypos - h, 0.0f, 1.0f},
        //     {xpos + w, -ypos - h, 1.0f, 1.0f}
        // };

        // printf("XPos: %f\n", xpos);
        // printf("YPos: %f\n", ypos);
        // printf("Width: %f\n", w);
        // printf("Height: %f\n", h);

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        // glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        // glBindBuffer(GL_ARRAY_BUFFER, 0);

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 10);
        // if(ch.textureID == 33 || ch.textureID == 106)
        //     x += (ch.advance >> 6) * size * 4;
        // else
        x += (ch.advance.x) * size*2;     //advance 1/64 of a pixel
        // y += (ch.advance.y >> 6) * size;     //advance 1/64 of a pixel
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    shader->stop();
    glEnable(GL_DEPTH_TEST);
}