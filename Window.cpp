#include "Window.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "Arrow.h"
#include <random>
#include <SDL_mixer.h>

Window::Window(int width, int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    width = width;
    height = height;
    if (auto error = SDL_CreateWindowAndRenderer( width, height,SDL_WINDOW_SHOWN, &window, &renderer )) {
        std::cout << "Nie udalo sie utworzyc okienka" << std::endl;
    }
    player = new Player(this);
    level = new Level(this);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
    music = Mix_LoadMUS("../music/time_for_adventure_WAV.wav");

    if (!music) {
        std::cerr << "SOUND ERROR:  " << Mix_GetError() << std::endl;
    }

    int channel = Mix_PlayMusic(music, -1);
    Mix_Volume(channel, MIX_MAX_VOLUME);

    level->levelTile = new Tile(this,500,350,200,100 );

    BuildLevel();

}

Window::~Window() {

    if(level) delete level;

    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

}

void Window::RenderAll() {

    SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
    SDL_RenderClear(renderer);

    Render(farBackground);
    Render(nearBackground);
    Render(levelDesign);
    Render(gameObjects);
    Render(foreGround);
    Render(UI);

    SDL_RenderPresent(renderer);

        if(counter%(75-int(player->positionX/350))==0)
            level->SpawnArrow();
        counter++;

}

void Window::Render(std::vector<GameObject *> objToRender) {

    for(auto go : objToRender){
        go->Render(*this);
    }

}

void Window::BuildLevel() {

    int blocksize = 150;
    int innerLoop = 25;

    // Seed dla generatora liczb losowych
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0); // Rozkład jednostajny na przedziale [0, 1)

    for (int i = 0; i != 10; i++) {
        level->farBackground = new FarBackground(this, -250 + (i * 1500), 0);
        level->nearBackground = new NearBackground(this, -250 + (i * 1000), 0);

        for (int j = 0; j != innerLoop; j++) {

            // Losowanie, czy utworzyć klocek, i jeśli tak, to ile
            int numBlocks = 1; // Domyślnie tworzymy jeden klocek
            double randVal = dis(gen);


            if (randVal < 0.2) {
                numBlocks = 0;
            } else if (randVal < 0.4) {
                numBlocks = 2;
            } else if (randVal < 0.6) {
                numBlocks = 3;
            }else if (randVal < 0.8) {
                numBlocks = 5;
            }

            for (int k = 0; k < numBlocks; k++) {
                level->levelTile = new Tile(this, 0 + (((i * innerLoop) + j) * blocksize) + (k * blocksize),
                                            (numBlocks==0)?2000:900-(k*blocksize), blocksize, blocksize);
                if(k+1 == numBlocks){
                    double coinChance = dis(gen);
                        if(coinChance < 0.3){
                            std::cout<<"TUTAJ DODAC monetki" << std::endl; //TODO DEATHSCREEN i MONETKI
                        }

                }
            }


        }
    }

}

void Window::Level::SpawnArrow() {

    std::random_device rd;
    std::mt19937 gen(rd());

    //ZAKRESY
    int posX = window->player->positionX;
    int minX_X = posX - 550;
    int maxX_X = posX + 550;
    int minY_Y = -100;
    int maxY_Y = 760;

    // Generator liczb losowych dla X
    std::uniform_int_distribution<> distribX(0, 1000);
    std::uniform_int_distribution<> distribX2(posX + 550, maxX_X);

    // Generator liczb losowych dla Y
    std::uniform_int_distribution<> distribY(minY_Y, maxY_Y);

    // Losowe wartości X i Y
    int randomX = (distribX(gen));
    int randomY = distribY(gen);


    Arrow* arr = nullptr;
    arr = new Arrow(this->window,posX + randomX,randomY);
    arr->speed += window->player->positionX / 500;
}
