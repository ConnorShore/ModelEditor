#include "Panel.h"

Panel::Panel(GUI* parent, float x, float y, float sx, float sy, std::string& textureFile, bool relativePos) 
    : GUI(parent,x,y,sx,sy,textureFile,relativePos)
{
    _type = GUI_PANEL;
}

Panel::Panel(float x, float y, float sx, float sy, std::string& textureFile) : GUI(x,y,sx,sy,textureFile)
{
    printf("Constructing panel\n");
    _type = GUI_PANEL;
    printf("Typed assigned\n");
}

Panel::Panel() : GUI()
{
    _type = GUI_PANEL;
}

Panel::~Panel()
{
}

void Panel::update()
{

}