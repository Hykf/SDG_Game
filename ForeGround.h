//
// Created by man91 on 14.05.2024.
//

#ifndef SGD_GAME_FOREGROUND_H
#define SGD_GAME_FOREGROUND_H


#include "GameObject.h"

class ForeGround : public GameObject{
public:
    ForeGround(Window* _window,int posX,int posY);
    ~ForeGround();

    float positionX = 250;
    float positionY = 250;

    int sizeX = 1500;
    int sizeY = 1000;

    void Render(Window& renderer) override;

};


#endif //SGD_GAME_FOREGROUND_H