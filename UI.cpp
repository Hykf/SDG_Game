#include "UI.h"
#include <SDL.h>
#include "Window.h"

UI::UI(Window *_window, int posX, int posY) {
    window = _window;
    window->UI.push_back(this);
    positionX = posX;
    positionY = posY;
}

UI::~UI() {
    window->UI.erase(std::find(window->UI.begin(),window->UI.end(),this));
}

void UI::Render(Window &renderer) {
    SDL_Rect square = { static_cast<int>(positionX), static_cast<int>(positionY), sizeX, sizeY };
    SDL_SetRenderDrawColor(renderer.renderer, r, g, b, a);
    SDL_RenderFillRect(renderer.renderer, &square);
}

void UI::ChangeColor(int _r, int _g, int _b, int _a) {
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

void UI::ChangeSize(int nx, int ny) {

    sizeX = nx;
    sizeY = ny;

}

