//
// Created by man91 on 13.05.2024.
//

#include "Arrow.h"
#include "Window.h"
#include <cmath>
#include <math.h>

Arrow::Arrow(Window *_window, int _posX, int _posY) {

    window = _window;
    posX = _posX;
    posY = _posY;
    window->gameObjects.push_back(this);


    boxCollision = new BoundingBox(posX,posY,sizeX,sizeY);
    boxCollision->collType = BoundingBox::DANGER;
    boxCollision->debugShow = 1;


    // Oblicz różnicę pozycji gracza i wroga
    double dirX = posX - window->player->positionX ;
    double dirY = posY - window->player->positionY   ;

    float angle = atan2(dirY, dirX) + M_PI;

    accX = cos(angle);
    accY = -sin(angle);

    if (accY > 0) {
        accY *= -1;
    }

}

void Arrow::Update() {

    posX = posX - (accX * speed);
    posY = posY - (accY * speed);

}


void Arrow::Render(Window &renderer) {

    Update();

    SDL_Rect square = { static_cast<int>(posX - window->player->positionX), static_cast<int>(posY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, 250, 0, 0, 255);
    SDL_RenderFillRect(renderer.renderer, &square);

    boxCollision->debugShow = 0;
    boxCollision->drawBoundingBox(window->renderer);

    int newPositionX =  static_cast<int>(posX) - int(window->player->positionX);
    int newPositionY =  static_cast<int>(posY);


    boxCollision->Move(newPositionX,newPositionY);
}




Arrow::~Arrow() {
    window->gameObjects.erase(std::find(window->gameObjects.begin(),window->gameObjects.end(),this));

}
