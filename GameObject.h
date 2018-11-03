#ifndef GAME_OBJECT
#define GAME_OBJECT

class GameObject {
public:
    GameObject() {}
    ~GameObject() {}

    unsigned int getID() {return id;}

    void setID(unsigned int id) {this->id = id;}

protected:
    unsigned int id;
};

#endif