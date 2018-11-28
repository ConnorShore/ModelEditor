#include "TextRenderer.h"

TextRenderer::TextRenderer()
{
    FT_Library ft;
    if(FT_Init_FreeType(&ft)) {
        printf("ERROR: Cannot init freetype\n");
    }
    printf("FT Librariy initilized\b");
}

TextRenderer::~TextRenderer()
{
    
}