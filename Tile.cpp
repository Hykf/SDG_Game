#include "Tile.h"
#include <SDL.h>
#include "Window.h"

Tile::Tile(Window* _window,int _posX, int _posY) {
    window = _window;
    window->gameObjects.push_back(this);
    positionX = _posX - (sizeX/2);
    positionY = _posY - (sizeY/2);
}

Tile::~Tile() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
}

void Tile::Render(Window &renderer) {

    SDL_Rect square = { static_cast<int>(positionX), static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 0, 255, 125, 255);
    SDL_RenderFillRect(renderer.renderer, &square);

}