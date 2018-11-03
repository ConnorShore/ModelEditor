#ifndef VERTEX
#define VERTEX

#include <GL/glew.h>

struct Position
{
    float x,y,z;
};

struct Normal 
{
    float x,y,z;
};

struct Color 
{
    float r,g,b,a;
};

struct Vertex {
    Position position;
    Normal normal;
    Color color;
};

#endif