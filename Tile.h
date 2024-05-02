#include "GameObject.h"

class Tile : public GameObject {
public:

    Tile(Window* _window,int posX,int posY);
    ~Tile();

    float positionX = 250;
    float positionY = 250;

    int sizeX = 50;
    int sizeY = 50;


    virtual void Render(Window& renderer) override;

};

