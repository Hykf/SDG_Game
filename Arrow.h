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
    int sizeX = 60;
    int sizeY = 30;
    float accX;
    float accY;
    float dirX;
    float dirY;
    float speed = 10.5f;


    virtual void Render(Window& renderer) override;
    void Update();
    double radiansToDegrees(double radians);
    double calculateRotationAngle();
};


#endif //SGD_GAME_ARROW_H
