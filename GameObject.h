#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "BoundingBox.h"

class Window;

class GameObject {
public:

    Window* window;
    BoundingBox* boxCollision;

    SDL_Texture* objectTexture = nullptr;
    int textureWidth;
    int textureHeight;

    virtual void Render(Window& renderer) = 0;
};

#endif // GAMEOBJECT_H

