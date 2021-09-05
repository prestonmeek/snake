#include "window.h"
#include "snake.h"
#include "fruit.h"

int main() 
{
    Window window = Window()
        .setTitle("SNAKE")
        .setScale(20)
        .setDimensions(20, 30)
        .setBackgroundColor(5, 5, 45)
        .create();

    Snake snake = Snake(window);
    Fruit fruit = Fruit(window);

    int score = 1;

    // main loop
    while (window.isOpen)
    {
        window.clear();
        window.handleEvents();

        if (!window.isOpen)
            break;

        // if snake eats fruit
        if (snake.getX() == fruit.getX() && snake.getY() == fruit.getY())
        {
            snake.addTail(INCREASE_FACTOR);
            fruit.respawn(snake);
            score += INCREASE_FACTOR;
        }
        
        snake.increaseCounter();

        if (snake.getCounter() >= int(250 / snake.getSpeed()))
        {
            snake.move();
            snake.resetCounter();
        }

        snake.render();
        fruit.render();

        window.displayScore(score);

        window.render();

        if (snake.checkIfLose())
        {
            snake.reset();
            fruit.reset();
            score = 1;
        }
    }

    return 0;
}