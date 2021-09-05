#include "window.h"

Window::Window()
{
    // default values
    title = "Window";
    fps = 60;
    scale = 1;
    width = 480;
    height = 640;
    backgroundColor = (SDL_Color){ 0, 0, 0, 255 };
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
}

Window& Window::setTitle(const char* title)
{
    this->title = title;

    return *this;
}

Window& Window::setFPS(int fps)
{
    this->fps = fps;

    return *this;
}

Window& Window::setScale(int scale)
{
    this->scale = scale;

    return *this;
}

Window& Window::setDimensions(int width, int height)
{
    this->width  = width;
    this->height = height;

    return *this;
}

Window& Window::setBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
{
    backgroundColor = (SDL_Color){ r, g, b, 255 };

    return *this;
}

Window& Window::create()
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * scale, height * scale, SDL_WINDOW_SHOWN);
    isOpen = true;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return *this;
}

SDL_Renderer* Window::getRenderer()
{
    return renderer;
}

int Window::getScale()
{
    return scale;
}

int Window::getWidth()
{
    return width;
}

int Window::getHeight()
{
    return height;
}

unordered_map<SDL_Keycode, bool> Window::getKeys()
{
    return keys;
}

void Window::clear()
{
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);
}

void Window::handleEvents()
{
    limitFPS();

    if (SDL_PollEvent(&event)) 
    {
        switch (event.type)
        {
            case SDL_QUIT:
                isOpen = false;
                destroy();
                    
                break;

            case SDL_KEYDOWN:
                keys.clear();
                keys[event.key.keysym.sym] = true;

                break;

            case SDL_KEYUP:
                keys[event.key.keysym.sym] = false;

                break;
        }
    }
}

void Window::limitFPS()
{
    a = chrono::system_clock::now();
    chrono::duration<double, milli> work_time = a - b;

    if (work_time.count() < 1000 / fps)
    {
        chrono::duration<double, milli> delta_ms(1000 / fps - work_time.count());
        chrono::milliseconds delta_ms_duration = chrono::duration_cast<chrono::milliseconds>(delta_ms);
        this_thread::sleep_for(chrono::milliseconds(delta_ms_duration.count()));
    }

    b = chrono::system_clock::now();
    chrono::duration<double, milli> sleep_time = b - a;

    // cout << "Time: " << (work_time + sleep_time).count() << "\n";
}

void Window::render()
{
    SDL_RenderPresent(renderer);
}

void Window::destroy()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Window::displayScore(int score)
{
    SDL_Color color = { 255, 255, 255, 255 };

    TTF_Font* font = TTF_OpenFont("arial.ttf", 15);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, ("SCORE: " + to_string(score)).c_str(), color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);

    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);

    SDL_Rect rect = { (width * scale) - text_width - 5, 0, text_width, text_height };
    SDL_RenderCopy(renderer, text, NULL, &rect);

    SDL_DestroyTexture(text);
}

SDL_Rect Window::createSquare(int x, int y, int size)
{
    SDL_Rect square = { x, y, size, size };

    return square;
}