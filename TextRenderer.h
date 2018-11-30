#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <ft2build.h>
#include FT_FREETYPE_H

#include "ShaderProgram.h"

#include <GL/glew.h>
#include <map>

struct Character
{
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    GLuint advance;
};

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void init();
    void renderText(ShaderProgram& shader, std::string text, float x, float y, float size, glm::vec4 color);

private:
    GLuint _vaoID, _vboID;
    std::map<GLchar, Character> _characters;
};

#endif