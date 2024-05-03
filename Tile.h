#include "LevelDesign.h"

class Tile : public LevelDesign {

public:
    Tile(Window* _window,int posX,int posY) : LevelDesign(_window, posX, posY) {}
};

