//
// Created by man91 on 12.05.2024.
//

#ifndef SGD_GAME_FARBACKGROUND_H
#define SGD_GAME_FARBACKGROUND_H


#include "GameObject.h"

class FarBackground : public GameObject{
public:

    FarBackground(Window* _window,int posX,int posY);
    ~FarBackground();

    float positionX = 250;
    float positionY = 250;

    int sizeX = 1500;
    int sizeY = 1000;

    void Render(Window& renderer) override;

};


#endif //SGD_GAME_FARBACKGROUND_H
