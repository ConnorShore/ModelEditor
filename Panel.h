#ifndef PANEL_H
#define PANEL_H

#include "GUI.h"

class Panel : public GUI
{
public:
    Panel(GUI* parent, float x, float y, float sx, float sy, std::string& textureFile, bool relativePos=true);
    Panel(float x, float y, float sx, float sy, std::string& textureFile);
    Panel();
    ~Panel();

    virtual void update();

private:

};

#endif