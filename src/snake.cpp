#include "snake.h"

Snake::Snake(Window& window) : window(window)
{
    head = {
        window.createSquare(0, 0, window.getScale()),
        { 1, 0 },
        HEAD_COLOR,
        true
    };

    dirHandler[SDLK_w] = { 0, -1 };
    dirHandler[SDLK_a] = { -1, 0 };
    dirHandler[SDLK_s] = { 0, 1 };
    dirHandler[SDLK_d] = { 1, 0 };

    // addTail(30);
}

void Snake::render()
{
    // rendering the head
    SDL_SetRenderDrawColor(window.getRenderer(), 0, HEAD_COLOR, 0, 255);
    SDL_RenderFillRect(window.getRenderer(), &head.body);

    // rendering the tail
    SDL_SetRenderDrawColor(window.getRenderer(), 0, TAIL_COLOR, 0, 255);

    for (SnakeBody t : tail)
        SDL_RenderFillRect(window.getRenderer(), &t.body);
}

int Snake::getX()
{
    return head.body.x;
}

int Snake::getY()
{
    return head.body.y;
}

int Snake::getTailX(int i)
{
    return tail[i].body.x;
}

int Snake::getTailY(int i)
{
    return tail[i].body.y;
}

int Snake::getTailLength()
{
    return tail.size();
}

void Snake::move()
{
    // set tail direction
    if (!tail.empty())
    {
        for (int i = tail.size() - 1; i > 0; i--)
            tail[i].dir = tail[i - 1].dir;

        tail[0].dir = head.dir;
    }

    // getting direction based on keyboard input
    for (const auto& [ key, isPressed ] : window.getKeys())
    {
        if (dirHandler.find(key) != dirHandler.end() && isPressed)
        {
            // if we aren't going in the complete opposite direction 
            // aka you can't press W if you last pressed S, can't press D if you last pressed A, etc.
            if (!(dirHandler[key].x == -head.dir.x && dirHandler[key].y == -head.dir.y))
                head.dir = dirHandler[key];
        }
    }

    // moving the head
    head.body.x += window.getScale() * head.dir.x;
    head.body.y += window.getScale() * head.dir.y;

    // handleWrapping(head);

    // moving the tail
    for (int i = 0; i < tail.size(); i++)
    {
        tail[i].body.x += window.getScale() * tail[i].dir.x;
        tail[i].body.y += window.getScale() * tail[i].dir.y;

        // handleWrapping(tail[i]);
    }
}

int Snake::getSpeed()
{
    return speed;
}

int Snake::getCounter()
{
    return counter;
}

void Snake::increaseCounter()
{
    counter++;
}

void Snake::resetCounter()
{
    counter = 0;
}

void Snake::addTail(int length)
{
    for (int i = 0; i < length; i++)
    {
        SnakeBody obj = tail.empty() ? head : tail[tail.size() - 1];

        tail.push_back({
            window.createSquare(
                obj.body.x - (window.getScale() * obj.dir.x), 
                obj.body.y - (window.getScale() * obj.dir.y), 
                window.getScale()
            ),
            obj.dir,
            TAIL_COLOR,
            false
        });
    }
}

// TODO: fix screen wrapping (sometimes causes segfaults idk y) and add it as a game option
void Snake::handleWrapping(SnakeBody& obj)
{
    SDL_Rect& body = obj.body;

    // check if object has touched screen - this just prevents glitches with screen wrapping w/ new tail squares
    if (body.x >= 0 && body.x < window.getWidth() * window.getScale() && body.y >= 0 && body.y < window.getHeight() * window.getScale())
        obj.hasTouchedScreen = true;

    if (obj.hasTouchedScreen)
    {
        if (body.x >= window.getWidth() * window.getScale())
            body.x = 0;
        else if (body.x < 0)
            body.x = window.getWidth() * window.getScale();

        if (body.y >= window.getHeight() * window.getScale())
            body.y = 0;
        else if (body.y < 0)
            body.y = window.getHeight() * window.getScale();
    }
}

bool Snake::checkIfLose()
{
    // check if snake is out of bounds
    if (head.body.x < 0 || head.body.y < 0 || head.body.x >= window.getWidth() * window.getScale() || head.body.y >= window.getHeight() * window.getScale())
        return true;

    // check if snake is eating itself
    for (SnakeBody t : tail)
    {
        if (head.body.x == t.body.x && head.body.y == t.body.y)
            return true;
    }

    return false;
}

void Snake::reset()
{
    tail.clear();
    
    head.body.x = 0;
    head.body.y = 0;

    head.dir = { 1, 0 };
}