

#include "NearBackground.h"
#include "Window.h"

NearBackground::NearBackground(Window *_window, int posX, int posY) {
    window = _window;
    window->nearBackground.push_back(this);
    positionX = posX;
    positionY = posY;
    objectTexture = IMG_LoadTexture(window->renderer, "../images/3.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);
}

NearBackground::~NearBackground() {
    auto it = window->nearBackground.erase(std::find(window->nearBackground.begin(),window->nearBackground.end(),this));

}

void NearBackground::Render(Window &renderer) {
    SDL_Rect dstRect = { static_cast<int>((positionX)-(window->player->positionX)/5), static_cast<int>(positionY), sizeX, sizeY }; // x i y pozycja na ekranie w i h rozmiar
    SDL_Rect srcRect = { 0 , 0, 380, 210 };; //

    SDL_RenderCopy(renderer.renderer, objectTexture, &srcRect, &dstRect);
}
