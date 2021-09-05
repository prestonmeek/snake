#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "window.h"
#include "square.h"

using namespace std;

const int INCREASE_FACTOR = 3;
const uint8_t HEAD_COLOR  = 150;
const uint8_t TAIL_COLOR  = 200;

struct Direction
{
    int x;
    int y;
};

struct SnakeBody
{
    SDL_Rect body;
    Direction dir;
    uint8_t color;
    bool hasTouchedScreen;
};

class Snake : public Square
{
    private:
        Window& window;

        const int speed = 40;

        int counter;

        SnakeBody head;
        vector<SnakeBody> tail;

        unordered_map<SDL_Keycode, Direction> dirHandler;

    public:
        Snake(Window& window);

        void render();

        int getX();
        int getY();
        int getTailX(int i);
        int getTailY(int i);
        int getTailLength();

        void move();

        int getSpeed();
        int getCounter();
        void increaseCounter();
        void resetCounter();

        void addTail(int length);
        void handleWrapping(SnakeBody& obj);
        bool checkIfLose();
        void reset();
};

#endif