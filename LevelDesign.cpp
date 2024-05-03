
#include "LevelDesign.h"

LevelDesign::LevelDesign(Window *_window, int posX, int posY) {
    window = _window;
    window->levelDesign.push_back(this);
    positionX = posX - (sizeX/2);
    positionY = posY - (sizeY/2);
}

LevelDesign::~LevelDesign() {
    window->levelDesign.erase(std::find(window->levelDesign.begin(),window->levelDesign.end(),this));
}

void LevelDesign::Render(Window &renderer) {
    SDL_Rect square = { static_cast<int>(positionX), static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 0, 255, 125, 255);
    SDL_RenderFillRect(renderer.renderer, &square);
}