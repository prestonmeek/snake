#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdint>
#include <unordered_map>

using namespace std;

class Window 
{
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        SDL_Event event;

        const char* title;
        int fps;
        int scale;
        int width;
        int height;
        SDL_Color backgroundColor;

        unordered_map<SDL_Keycode, bool> keys;

        chrono::system_clock::time_point a;
        chrono::system_clock::time_point b;

    public:
        Window();

        bool isOpen;

        Window& setTitle(const char* title);
        Window& setFPS(int fps);
        Window& setScale(int scale);
        Window& setDimensions(int width, int height);

        Window& setBackgroundColor(uint8_t r, uint8_t g, uint8_t b);

        Window& create();

        SDL_Renderer* getRenderer();
        int getScale();
        int getWidth();
        int getHeight();
        unordered_map<SDL_Keycode, bool> getKeys();

        void clear();
        void handleEvents();
        void limitFPS();
        void render();
        void destroy();

        void displayScore(int score);

        SDL_Rect createSquare(int x, int y, int size);
};

#endif