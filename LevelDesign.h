#pragma once
#include <SDL.h>
#include "BoundingBox.h"
#include "Window.h"
#include "GameObject.h"


class LevelDesign : public GameObject {

public:

        LevelDesign(Window* _window,int posX,int posY);
        ~LevelDesign();

        float positionX = 250;
        float positionY = 250;

        int sizeX = 50;
        int sizeY = 50;

        virtual void Render(Window& renderer) override;

    };



