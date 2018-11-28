#ifndef BUTTON
#define BUTTON

#include "GUI.h"

class Button : public GUI
{
public:
    Button(GUI* parent, float x, float y, float sx, float sy, std::string& textureFile, bool relativePos=true);
    Button(float x, float y, float sx, float sy, std::string& textureFile);
    Button();
    ~Button();

    virtual void update();

    void onClick();

    bool isEnabled() {return _enabled;}
    
    void setEnabled(bool enabled) {_enabled = enabled;}

private:
    bool _enabled;
};

#endif