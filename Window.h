#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <SDL_image.h>
#include "Player.h"
#include "FarBackground.h"
#include "NearBackground.h"
#include <vector>

class Tile;
class GameObject;

class Window {
public:

    struct Level{
        FarBackground* farBackground = nullptr;
        NearBackground* nearBackground = nullptr;
        Tile* levelTile;
    };

    Window(int width, int height);
    ~Window();

    SDL_Window *window;
    SDL_Renderer *renderer;
    Player* player;

    Level* level = nullptr;

    int width = 1000;
    int height= 1000;

    float DeltaTime = 0.4;


    std::vector<GameObject*> farBackground;
    std::vector<GameObject*> nearBackground;
    std::vector<GameObject*> levelDesign;
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> foreGround;
    std::vector<GameObject*> UI;

    void Render(std::vector<GameObject*> objToRender);
    void RenderAll();
    void BuildLevel();
};

#endif // WINDOW_H
