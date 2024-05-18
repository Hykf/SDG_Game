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
    objectSpawnTime = SDL_GetTicks();


    boxCollision = new BoundingBox(posX,posY,sizeX,sizeY);
    boxCollision->collType = BoundingBox::DANGER;
    boxCollision->debugShow = 1;

    double dirX = 500 - (posX - window->player->positionX);
    double dirY = window->player->positionY - posY;

    double length = sqrt((dirX * dirX) + (dirY * dirY));//To dlugosc wektora SQRT(A^2 + B^2)

    if (length != 0) { // Unit vec
        accX = dirX / length;
        accY = dirY / length;
    } else {
        accX = 0;
        accY = 0;
    }

    objectTexture = IMG_LoadTexture(window->renderer, "../images/arrow.png");
    SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

}

void Arrow::Update() {

    CheckTime();

    posX += accX * speed;
    posY += accY * speed;


}


void Arrow::Render(Window &renderer) {

    Update();

    SDL_Rect square = { static_cast<int>(posX - window->player->positionX), static_cast<int>(posY), sizeX, sizeY };
    //SDL_SetRenderDrawColor(renderer.renderer, 250, 0, 0, 255);
    //SDL_RenderFillRect(renderer.renderer, &square);

    boxCollision->debugShow = 0;
    boxCollision->drawBoundingBox(window->renderer);

    int newPositionX =  static_cast<int>(posX) - int(window->player->positionX);
    int newPositionY =  static_cast<int>(posY);


    SDL_Rect dstRect = { newPositionX, static_cast<int>(newPositionY), sizeX, sizeY };
    SDL_Rect srcRect = { 0 , 0, 17, 5 };; //


    double rotationAngle = calculateRotationAngle();

    SDL_RendererFlip flip;
    SDL_RenderCopyEx(renderer.renderer, objectTexture, &srcRect, &dstRect,-rotationAngle, NULL, flip);

    boxCollision->Move(newPositionX,newPositionY);

    CheckTime();
}

void Arrow::CheckTime() {
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - objectSpawnTime >= 20000) {
        deleted = true;
        window->gameObjects.erase( std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
    }
}

Arrow::~Arrow() {
    window->gameObjects.erase( std::find(window->gameObjects.begin(),window->gameObjects.end(),this));
}

double Arrow::radiansToDegrees(double radians) {
    return  radians * 180.0 / M_PI;;
}

double Arrow::calculateRotationAngle() {
    double angleRadians = atan2(accY, accX);
    double angleDegrees = radiansToDegrees(angleRadians);
    return -angleDegrees;
}

