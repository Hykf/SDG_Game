#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <vector>

class GameObject;

class Window {
public:

    Window(int width, int height);
    ~Window();

    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;

    std::vector<GameObject*> gameObjects;


    void RenderAll();
};

#endif // WINDOW_H
