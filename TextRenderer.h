#ifndef TEXT_RENDERER
#define TEXT_RENDERER

#include <ft2build.h>
#include FT_FREETYPE_H

#include "TextShader.h"

#include <GL/glew.h>
#include <map>

struct Character
{
    GLuint textureID;
    glm::ivec2 size;
    glm::ivec2 bearing;
    glm::ivec2 advance;
};

class TextRenderer
{
public:
    TextRenderer();
    ~TextRenderer();

    void init(TextShader* shader, int width, int height);
    void prepare(TextShader* shader, int width, int height);
    void end(TextShader* shader);
    void renderText(TextShader* shader, std::string text, float x, float y, float size, glm::vec3 color);

private:
    GLuint _vaoID, _vboID;
    std::map<GLchar, Character> _characters;
};

#endif