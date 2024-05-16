#include "Window.h"
#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Tile.h"
#include "Arrow.h"
#include <random>
#include "Coin.h"
#include <windows.h>


Window::Window(int width, int height) {
    SDL_Init( SDL_INIT_EVERYTHING );
    width = width;
    height = height;
    if (auto error = SDL_CreateWindowAndRenderer( width, height,SDL_WINDOW_SHOWN, &window, &renderer )) {
        std::cout << "Nie udalo sie utworzyc okienka" << std::endl;
    }
    player = new Player(this);
    level = new Level(this);

    ///
    InitMusic();
   std::cout<< GetLastError();
   ///

    level->levelTile = new Tile(this,500,350,200,100 );
    BuildLevel();

}

Window::~Window() {

    if(level) delete level;
    alSourceStop(backgroundMusicSource);
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();

}

void Window::RenderAll() {

    //PlaySound(TEXT("BackgroundMusicWav.wav"), NULL,  SND_FILENAME |  SND_LOOP | SND_ASYNC | SND_NOSTOP);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if(player->alive){

        Render(farBackground);
        Render(nearBackground);
        Render(levelDesign);
        Render(gameObjects);
        Render(foreGround);
        Render(UI);

        if(counter%(65-int(player->positionX/350))==0)

            for(int i = 0; i != (1+ int(player->positionX/5000)) ;i++){
                level->SpawnArrow();
            }

        counter++;
    }else{

        const int finalScore = player->score * (player->positionX/1000);

        farBackground.clear();
        nearBackground.clear();
        levelDesign.clear();
        gameObjects.clear();
        foreGround.clear();
        UI.clear();

        SDL_Texture* objectTexture = IMG_LoadTexture(renderer, "../images/SKULL.png");
        int textureWidth;
        int textureHeight;
        SDL_QueryTexture(objectTexture, NULL, NULL, &textureWidth, &textureHeight);

        SDL_Rect dstRect = { static_cast<int>(250), static_cast<int>(250), 500, 500 }; // x i y pozycja na ekranie w i h rozmiar
        SDL_Rect srcRect = { 0 , 0, 32, 32 }; // x i y wspolrzedne lewego gornego rogu w i h wspolrzednego prawego dolnego rogu //TODO ANIMACJA

        SDL_RendererFlip flip;

        SDL_RenderCopyEx(renderer, objectTexture, &srcRect, &dstRect,0.0, NULL, flip);
        alSourceStop(backgroundMusicSource);

        if(counter%100==0){
            std::cout<< "FINAL SCORE: " << finalScore << std::endl;

        }

        if(makeLastSound){
            PlaySound(TEXT("../sounds/explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
            makeLastSound = false;
        }

    }

    SDL_RenderPresent(renderer);

}

void Window::Render(std::vector<GameObject *> objToRender) {

    for(auto go : objToRender){

        if(go)
         go->Render(*this);
    }

}

void Window::BuildLevel() {
    int blocksize = 150;
    int innerLoop = 25;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i != 10; i++) {

        level->farBackground = new FarBackground(this, -250 + (i * 1500), 0);
        level->nearBackground = new NearBackground(this, -250 + (i * 1000), 0);
        level->foreGround = new ForeGround(this,-250 + (i * 2000), 0);

        for (int j = 0; j != innerLoop; j++) {

            int numBlocks = 1;
            double randVal = dis(gen);

            if (randVal < 0.2) {
                numBlocks = 0;
            } else if (randVal < 0.4) {
                numBlocks = 2;
            } else if (randVal < 0.6) {
                numBlocks = 3;
            } else if (randVal < 0.8) {
                numBlocks = 5;
            }

            for (int k = 0; k < numBlocks; k++) {

                int posX = 0 + (((i * innerLoop) + j) * blocksize) + (k * blocksize);
                int posY = (numBlocks == 0) ? 2000 : 900 - (k * blocksize);

                level->levelTile = new Tile(this, posX, posY, blocksize, blocksize);

                if (k == numBlocks - 1) {
                    double coinChance = dis(gen);
                    if (coinChance < 0.3) {
                        level->coin = new Coin(this, posX + blocksize, posY - (blocksize - 50));
                    }

                }
            }
        }
    }
}

bool Window::loadWavFile(const char *filename, ALuint buffer) {

    FILE* file = fopen(filename, "rb");
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    const size_t MAX_WAV_SIZE = 10 * 1024 * 1024;
    if (fileSize > MAX_WAV_SIZE) {
        std::cerr << "File size exceeds maximum allowed size." << std::endl;
        fclose(file);
        return false;
    }

    char* data = new char[fileSize];

    size_t bytesRead = fread(data, 1, fileSize, file);
    if (bytesRead != fileSize) {
        std::cerr << "Failed to read file: " << filename << std::endl;
        fclose(file);
        delete[] data;
        return false;
    }

    fclose(file);
    alBufferData(buffer, AL_FORMAT_MONO16, data, fileSize, 75000);
    delete[] data;

    return true;
}

void Window::InitMusic() {

    ALCdevice* device = alcOpenDevice(nullptr);
    ALCcontext* context = alcCreateContext(device, nullptr);
    ALenum error;

    if (!alcMakeContextCurrent(context)) {

        std::cerr << "Failed to make OpenAL context current" << std::endl;
        alcDestroyContext(context);
        alcCloseDevice(device);
    }

    alGenBuffers(1, &backgroundMusicBuffer);

    if (alGetError() != AL_NO_ERROR) std::cerr << "Failed to make sound buffor: " << alGetString(error) << std::endl;

    loadWavFile("../music/time_for_adventure_WAV.wav", backgroundMusicBuffer);

    if (alGetError() != AL_NO_ERROR) std::cerr << "Failed to load music file: " << alGetString(error) << std::endl;

    alGenSources(1, &backgroundMusicSource);

    if (alGetError() != AL_NO_ERROR) std::cerr << "Failed to create music source: " << alGetString(error) << std::endl;

    alSourcei(backgroundMusicSource, AL_BUFFER, backgroundMusicBuffer);
    alSourcei(backgroundMusicSource, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR) std::cerr << "Błąd przy ustawianiu bufora dźwięku dla źródła: " << alGetString(error) << std::endl;

    alSourcePlay(backgroundMusicSource);

    if (alGetError() != AL_NO_ERROR) std::cerr << "Błąd przy odtwarzaniu muzyki: " << alGetString(error) << std::endl;

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

    std::uniform_int_distribution<> distribX(-100, 1100);

    std::uniform_int_distribution<> distribY(minY_Y, maxY_Y);

    int randomX = (distribX(gen));
    int randomY = distribY(gen);

    Arrow* arr = nullptr;

    if(window->counter%2==0){
        arr = new Arrow(this->window,posX + -300,randomY);
    }else{
        arr = new Arrow(this->window,posX + 1000,randomY);
    }


    arr->speed += window->player->positionX / 500;
}
