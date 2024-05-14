
#include "Coin.h"
#include "Window.h"

Coin::Coin(Window *_window, int _posX, int _posY) {
    window = _window;
    posX = _posX;
    posY = _posY;
    window->gameObjects.push_back(this);


    boxCollision = new BoundingBox(posX,posY,sizeX,sizeY);
    boxCollision->collType = BoundingBox::COIN;
    boxCollision->debugShow = 1;

    objectTexture = IMG_LoadTexture(window->renderer, "../images/coin.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}


void Coin::Render(Window &renderer) {
    SDL_Rect square = { static_cast<int>(posX - window->player->positionX), static_cast<int>(posY), sizeX, sizeY };
    //SDL_SetRenderDrawColor(renderer.renderer, 250, 255, 0, 255);
    //SDL_RenderFillRect(renderer.renderer, &square);

    boxCollision->debugShow = 0;
    boxCollision->drawBoundingBox(window->renderer);

    int newPositionX =  static_cast<int>(posX) - int(window->player->positionX);
    int newPositionY =  static_cast<int>(posY);

    if(counter%20==0){
        cc++;
        cc = cc% 12;
    }


    SDL_Rect dstRect = { newPositionX, static_cast<int>(newPositionY), sizeX, sizeY };
    SDL_Rect srcRect = { 3 + (cc * 16) , 3, 9, 10 };; //




    counter++;


    SDL_RendererFlip flip;
    SDL_RenderCopyEx(renderer.renderer, objectTexture, &srcRect, &dstRect,0.0f, NULL, flip);

    boxCollision->Move(newPositionX,newPositionY);
}



Coin::~Coin() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));

}
