#include "fruit.h"

Fruit::Fruit(Window& window) : window(window)
{
    body = window.createSquare(START_X * window.getScale(), START_Y * window.getScale(), window.getScale());

    // initialize random seed
    srand(time(NULL));
}

void Fruit::render()
{
    SDL_SetRenderDrawColor(window.getRenderer(), FRUIT_COLOR, 0, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &body);
}

int Fruit::getX()
{
    return body.x;
}

int Fruit::getY()
{
    return body.y;
}

void Fruit::respawn(Snake& snake)
{
    int x;
    int y;
    bool isFruitTouchingSnake;

    do
    {
        isFruitTouchingSnake = false;

        x = (rand() % window.getWidth()) * window.getScale();
        y = (rand() % window.getHeight()) * window.getScale();

        // check if fruit is touching snake - if it is, rerun loop
        if (x == snake.getX() && y == snake.getY())
            isFruitTouchingSnake = true;

        for (int i = 0; i < snake.getTailLength(); i++)
        {
            if (x == snake.getTailX(i) && y == snake.getTailY(i))
                isFruitTouchingSnake = true;
        }
    } 
    while (isFruitTouchingSnake);

    body.x = x;
    body.y = y;
}

void Fruit::reset()
{
    body.x = START_X * window.getScale();
    body.y = START_Y * window.getScale();
}