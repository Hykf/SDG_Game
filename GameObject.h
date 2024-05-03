#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <algorithm>
#include <SDL.h>
#include <iostream>
#include "BoundingBox.h"

class Window;

class GameObject {
public:

    Window* window;
    BoundingBox* boxCollision;

    virtual void Render(Window& renderer) = 0;
};

#endif // GAMEOBJECT_H

