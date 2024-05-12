#include "LevelDesign.h"

class Tile : public LevelDesign {

public:

    Tile(Window* _window,int posX,int posY) : LevelDesign(_window, posX, posY) {

        objectTexture = IMG_LoadTexture(window->renderer, "../images/world_tileset.png");
        SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

    }


    Tile(Window* _window,int posX,int posY,int _sizeX,int _sizeY) : LevelDesign(_window, posX, posY) {
        sizeX = _sizeX;
        sizeY = _sizeY;
        boxCollision->width = sizeX;
        boxCollision->height = sizeY;

        objectTexture = IMG_LoadTexture(window->renderer, "../images/world_tileset.png");
        SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

    }


};

