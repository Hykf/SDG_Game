#include "BoundingBox.h"

bool BoundingBox::CheckCollision(const BoundingBox &otherBox, int dx, int dy) const {
    int thisRight = x + width + dx;
    int otherRight = otherBox.x + otherBox.width;
    int thisBottom = y + height + dy;
    int otherBottom = otherBox.y + otherBox.height;

    if (thisRight < otherBox.x || x + dx > otherRight ||
        thisBottom < otherBox.y || y + dy > otherBottom) {
        return false;
    }
    return true;
}

void BoundingBox::drawBoundingBox(SDL_Renderer *renderer) const {

    if(debugShow){
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        SDL_Rect rect = { x, y, width, height };

        SDL_RenderDrawRect(renderer, &rect);
    }

}

void BoundingBox::Move(int nx, int ny) {

    x = nx;
    y = ny;

}

int BoundingBox::CollisionDirection(const BoundingBox& otherBox) {

    int thisRight = x + width;
    int otherRight = otherBox.x + otherBox.width;
    int thisBottom = y + height;
    int otherBottom = otherBox.y + otherBox.height;

    int overlapX = (thisRight - otherBox.x) - (otherRight - x);
    int overlapY = (thisBottom - otherBox.y) - (otherBottom - y);

    if (std::abs(overlapX) < std::abs(overlapY)) {

        if (overlapY > 0) {
            return 0; // Kolizja z góry
        } else {
            return 2; // Kolizja z dołu
        }

    } else {

        if (overlapX > 0) {
            return 3; // Kolizja z lewej
        } else {
            return 1; // Kolizja z prawej
        }

    }


    return -1;
}
