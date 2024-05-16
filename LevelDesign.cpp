
#include "LevelDesign.h"
#include "BoundingBox.h"

LevelDesign::LevelDesign(Window *_window, int posX, int posY) {
    window = _window;
    window->levelDesign.push_back(this);
    positionX = posX - (sizeX/2);
    positionY = posY - (sizeY/2);
    boxCollision = new BoundingBox(positionX,positionY,sizeX,sizeY);
    boxCollision->debugShow = 1;
}

LevelDesign::~LevelDesign() {
    window->levelDesign.erase(std::find(window->levelDesign.begin(),window->levelDesign.end(),this));
}

void LevelDesign::Render(Window &renderer) {

    SDL_Rect square = { static_cast<int>(positionX) - int(window->player->positionX), static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 0, 0, 0, 0);
    SDL_RenderFillRect(renderer.renderer, &square);


    boxCollision->debugShow = 0;
    boxCollision->drawBoundingBox(window->renderer);

    int newPositionX =  static_cast<int>(positionX) - int(window->player->positionX);
    int newPositionY =  static_cast<int>(positionY);


    boxCollision->Move(newPositionX,newPositionY);

    SDL_Rect dstRect = { newPositionX, static_cast<int>(positionY), sizeX, sizeY }; // x i y pozycja na ekranie w i h rozmiar
    SDL_Rect srcRect = { 0 + (cc * 16), 0, 16, 16 };; //


    if (counter % 50 == 0) {
        //cc++;
       // cc = cc % 4;
         // Poprawiono obliczenia
    }

    SDL_RenderCopy(renderer.renderer, objectTexture, &srcRect, &dstRect);
    counter++;

}
