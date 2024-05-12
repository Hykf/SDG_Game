//
// Created by man91 on 12.05.2024.
//

#ifndef SGD_GAME_NEARBACKGROUND_H
#define SGD_GAME_NEARBACKGROUND_H

#include "GameObject.h"

class NearBackground : public GameObject{
public:

    NearBackground(Window* _window,int posX,int posY);
    ~NearBackground();

    float positionX = 250;
    float positionY = 250;

    int sizeX = 1500;
    int sizeY = 500;

    void Render(Window& renderer) override;

};


#endif //SGD_GAME_NEARBACKGROUND_H
