

#ifndef SGD_GAME_COIN_H
#define SGD_GAME_COIN_H


#include "GameObject.h"

class Coin : public GameObject{
public:
    Coin(Window* _window,int _posX, int _posY);
    ~Coin();


    int posX;
    int posY;
    int sizeX = 50;
    int sizeY = 50;
    int cc = 0;
    int counter = 0;

    virtual void Render(Window& renderer) override;
};


#endif //SGD_GAME_COIN_H
