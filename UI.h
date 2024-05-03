#include "GameObject.h"

class UI : public GameObject{
public:
    UI(Window* _window,int posX,int posY);
    ~UI();

    float positionX = 250;
    float positionY = 750;

    int sizeX = 500;
    int sizeY = 20;

    int a = 255;
    int r = 255;
    int g = 255;
    int b = 255;



    void ChangeColor(int _r,int _g, int _b , int _a);
    void ChangeSize(int nx, int ny);
    virtual void Render(Window& renderer) override;

};

