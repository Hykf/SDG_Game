#include <algorithm>
#include "FarBackground.h"
#include "Window.h"


FarBackground::FarBackground(Window *_window, int posX, int posY) {
    window = _window;
    window->farBackground.push_back(this);
    positionX = posX;
    positionY = posY;
    objectTexture = IMG_LoadTexture(window->renderer, "../images/world_tileset.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
}

FarBackground::~FarBackground() {
    auto it = window->farBackground.erase(std::find(window->farBackground.begin(),window->farBackground.end(),this));
}

void FarBackground::Render(Window &renderer) {
    SDL_Rect dstRect = { static_cast<int>((positionX)-(window->player->positionX)/15), static_cast<int>(positionY), sizeX, sizeY }; // x i y pozycja na ekranie w i h rozmiar
    SDL_Rect srcRect = { 0 , 144, 16, 111 };; //

    SDL_RenderCopy(renderer.renderer, objectTexture, &srcRect, &dstRect);
}
