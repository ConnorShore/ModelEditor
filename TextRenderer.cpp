#include "TextRenderer.h"
#include <stdio.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

TextRenderer::TextRenderer() : _vaoID(0), _vboID(0)
{
}

TextRenderer::~TextRenderer()
{
}

void TextRenderer::init(TextShader* shader, int width, int height)
{
    shader->start();
    glm::mat4 proj = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
    shader->loadProjectionMatrix(proj);

    FT_Library ft;
    if(FT_Init_FreeType(&ft))
        printf("Failed to initialize FreeType Library\n");
    
    FT_Face face;
    if(FT_New_Face(ft, "Fonts/arial.ttf", 0, &face))
        printf("Failed to load font\n");
    
    FT_Set_Pixel_Sizes(face, 0, 48);
    
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
                     0, GL_ALPHA, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
                     
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character;
        character.textureID = texID;
        character.size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        character.bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        character.advance.x = face->glyph->advance.x;
        character.advance.y = face->glyph->advance.y;
        _characters.insert(std::pair<GLchar, Character>(i, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    //Create VAO and VBO
    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    glGenBuffers(1, &_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader->stop();
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
    shader->start();
    shader->loadColor(color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(_vaoID);

    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        printf("Character: %c\n", *c);
        Character ch = _characters[*c];
        float xpos = x + ch.bearing.x * size;
        float ypos = y - (ch.size.y - ch.bearing.y) * size;

        float w = ch.size.x * size;
        float h = ch.size.y * size;

        // float vertices[6][4] = {
        //     { xpos, ypos + h, 0.0f, 0.0f},
        //     { xpos, ypos, 0.0f, 1.0f},
        //     { xpos + w, ypos, 1.0f, 1.0f},

        //     { xpos, ypos + h, 0.0f, 0.0f},
        //     { xpos + w, ypos, 1.0f, 1.0f},
        //     { xpos + w, ypos + h, 1.0f, 0.0f},
        // };

        GLfloat vertices[4][4] = {
            {xpos, -ypos, 0.0f, 0.0f},
            {xpos + w, -ypos, 1.0f, 0.0f},
            {xpos, -ypos - h, 0.0f, 1.0f},
            {xpos + w, -ypos - h, 1.0f, 1.0f}
        };

        printf("XPos: %f\n", xpos);
        printf("YPos: %f\n", ypos);
        printf("Width: %f\n", w);
        printf("Height: %f\n", h);

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, _vboID);
        // glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        x += (ch.advance.x >> 6) * size;     //advance 1/64 of a pixel
        y += (ch.advance.y >> 6) * size;     //advance 1/64 of a pixel
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shader->stop();
}