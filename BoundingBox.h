#include "SDL.h"

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H


class BoundingBox {
public:
    int x, y;
    int width, height;
    bool debugShow = 0;


    BoundingBox(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}

    bool CheckCollision(const BoundingBox& otherBox) const;
    void drawBoundingBox(SDL_Renderer* renderer) const;
    void Move(int nx , int ny);
    int CollisionDirection(const BoundingBox& otherBox);
};

#endif // BOUNDINGBOX_H
