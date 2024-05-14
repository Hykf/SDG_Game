//
// Created by man91 on 14.05.2024.
//

#include "ForeGround.h"
#include "Window.h"

ForeGround::ForeGround(Window *_window, int posX, int posY) {
    window = _window;
    window->foreGround.push_back(this);
    positionX = posX;
    positionY = posY;
    objectTexture = IMG_LoadTexture(window->renderer, "../images/1.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
}

ForeGround::~ForeGround() {
    window->foreGround.erase(std::find(window->foreGround.begin(),window->foreGround.end(),this));

}

void ForeGround::Render(Window &renderer) {
    SDL_Rect dstRect = { static_cast<int>((positionX)-(window->player->positionX)), static_cast<int>(positionY), sizeX, sizeY };
    SDL_Rect srcRect = { 0 , 0, 380, 210 };; //

    SDL_RenderCopy(renderer.renderer, objectTexture, &srcRect, &dstRect);
}
