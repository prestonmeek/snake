#ifndef SQUARE_H
#define SQUARE_H

#include <SDL2/SDL.h>
#include <utility>

using namespace std;

class Square 
{
    public:
        virtual void render() = 0;
        virtual int getX() = 0;
        virtual int getY() = 0;
};

#endif