//
// Created by man91 on 13.05.2024.
//

#ifndef SGD_GAME_ARROW_H
#define SGD_GAME_ARROW_H


#include "GameObject.h"

class Arrow : public GameObject {
public:
    Arrow(Window* _window,int _posX, int _posY);
    ~Arrow();

    int posX;
    int posY;
    int sizeX = 20;
    int sizeY = 10;
    float accX;
    float accY;
    float dirX;
    float dirY;
    float speed = 5.5f;


    virtual void Render(Window& renderer) override;
    void Update();

};


#endif //SGD_GAME_ARROW_H
