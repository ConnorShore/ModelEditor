#ifndef VERTEX
#define VERTEX

struct Position
{
    float x,y,z;
};

struct Color 
{
    GLubyte r,g,b,a;
};

struct Vertex {
    Position position;
    Color color;
};

#endif