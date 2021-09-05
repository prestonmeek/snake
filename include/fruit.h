#ifndef FRUIT_H
#define FRUIT_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <stdlib.h>
#include <time.h>
#include "window.h"
#include "snake.h"
#include "square.h"

using namespace std;

const uint8_t FRUIT_COLOR = 255;
const int START_X = 5;
const int START_Y = 5;

class Fruit : public Square
{
    private:
        Window& window;
        
        SDL_Rect body;

    public:
        Fruit(Window& window);

        void render();
        int getX();
        int getY();

        void respawn(Snake& snake);
        void reset();
};

#endif