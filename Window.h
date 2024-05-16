#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"
#include <SDL_image.h>
#include "Player.h"
#include "FarBackground.h"
#include "NearBackground.h"
#include "ForeGround.h"
#include <vector>
#include "Coin.h"
#include <AL/al.h>
#include <AL/alc.h>


class Tile;
class GameObject;

class Window {
public:

    struct Level{

        Level(Window* _window){
            window = _window;
        }

        FarBackground* farBackground = nullptr;
        NearBackground* nearBackground = nullptr;
        ForeGround* foreGround = nullptr;
        Window* window = nullptr;
        Tile* levelTile;
        Coin* coin =nullptr;

        void SpawnArrow();
    };

    Window(int width, int height);
    ~Window();

    SDL_Window *window;
    SDL_Renderer *renderer;
    Player* player;
    Level* level = nullptr;

    int width = 1000;
    int height= 1000;
    uint64_t counter = 0;
    bool makeLastSound = true;

    float DeltaTime = 0.4;
    ALuint backgroundMusicBuffer;
    ALuint backgroundMusicSource;

    std::vector<GameObject*> farBackground;
    std::vector<GameObject*> nearBackground;
    std::vector<GameObject*> levelDesign;
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> foreGround;
    std::vector<GameObject*> UI;

    void Render(std::vector<GameObject*> objToRender);
    void RenderAll();
    void BuildLevel();
    bool loadWavFile(const char* filename, ALuint buffer);
    void InitMusic();
};

#endif // WINDOW_H
