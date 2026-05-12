/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** snake.cpp
*/

#include "Snake.hpp"
#include <cstdlib>

extern "C" std::unique_ptr<ARCADE::IGameModule> entryPoint()
{
    return std::make_unique<ARCADE::Snake>();
}

void ARCADE::Snake::init(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    if (_snake.size() > 0)
        return;

    this->tick = 0;
    this->_score = 0;
    this->_direction = faceDirection::EAST;
    this->_nextDirection = this->_direction;
    this->_lastUpdate = std::chrono::high_resolution_clock::now();

    this->_grid.resize(16, std::vector<element>(16, element::VOID));
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            if (x == 0 || x == 15 || y == 0 || y == 15) {
                this->_grid[y][x] = element::WALL;

                auto wall = display->createRectangle();
                wall->setPosX(x * _tileSize);
                wall->setPosY(y * _tileSize);
                wall->setWidth(_tileSize);
                wall->setHeight(_tileSize);
                wall->setColor(ARCADE::Color::White);
                state.storeShape(std::move(wall), "wall_" + std::to_string(x) + "_" + std::to_string(y));
            }
        }
    }

    _snake.push_back({5, 5});
    _grid[5][5] = element::HEAD;

    auto head = display->createRectangle();
    head->setWidth(_tileSize);
    head->setHeight(_tileSize);
    head->setPosX(5 * 40);
    head->setPosY(5 * 40);
    head->setColor(ARCADE::Color::Green);
    state.storeShape(std::move(head), "snake_0");

    spawFruit(display, state);

    _lastRenderdSize = _snake.size();

    this->_running = true;
}

void ARCADE::Snake::stop()
{
    this->_running = false;
}

void ARCADE::Snake::handleKeys(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    (void)state;
    if (display->isKeyPressed("up") && this->_direction != faceDirection::SOUTH)
        this->_nextDirection = faceDirection::NORTH;
    if (display->isKeyPressed("left") && this->_direction != faceDirection::EAST)
        this->_nextDirection = faceDirection::WEST;
    if (display->isKeyPressed("down") && this->_direction != faceDirection::NORTH)
        this->_nextDirection = faceDirection::SOUTH;
    if (display->isKeyPressed("right") && this->_direction != faceDirection::WEST)
        this->_nextDirection = faceDirection::EAST;
}

void ARCADE::Snake::update(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    if (_gameover)
        return this->gameOver(display, state);

    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> delta = now - _lastUpdate;
    _lastUpdate = now;

    _timer += delta.count();
    if (_timer < _delay)
        return;
    _timer -= _delay;

    tick++;
    this->_direction = this->_nextDirection;

    auto head = _snake.front();
    int newX = head.first;
    int newY = head.second;

    auto oldHead = _snake.front();
    switch (_direction) {
        case faceDirection::NORTH: newY--; break;
        case faceDirection::SOUTH: newY++; break;
        case faceDirection::WEST:  newX--; break;
        case faceDirection::EAST:  newX++; break;
    }

    if (_grid[newY][newX] == element::WALL || _grid[newY][newX] == element::TAIL) {
        deleteSnake(state);
        state.removeShape("fruit");
        _gameover = true;
        // stop();
        return;
    }

    bool grow = (_grid[newY][newX] == element::APPLE);

    _snake.push_front({newX, newY});
    _grid[newY][newX] = element::HEAD;
    _grid[oldHead.second][oldHead.first] = element::TAIL;
    
    if (!grow) {
        auto tail = _snake.back();
        _grid[tail.second][tail.first] = element::VOID;
        _snake.pop_back();
    } else {
        _score += 1;
        spawFruit(display, state);
    }

    int i = 0;
    for (auto& part : _snake) {
        std::string name = "snake_" + std::to_string(i);

        if (_snake.size() > _lastRenderdSize) {
            auto newRect = display->createRectangle();
            newRect->setWidth(_tileSize);
            newRect->setHeight(_tileSize);
            newRect->setColor(ARCADE::Color::Green);
            state.storeShape(std::move(newRect), name);
        }

        auto& r = state.getShape(name);
        r->setPosX(part.first * _tileSize);
        r->setPosY(part.second * _tileSize);

        i++;
    }
    _lastRenderdSize = _snake.size();
}

bool ARCADE::Snake::isRunning() const
{
    return this->_running;
}

std::size_t ARCADE::Snake::getScore() const
{
    return _score;
}

void ARCADE::Snake::spawFruit(std::unique_ptr<ARCADE::ADisplayModule>& display, ARCADE::GameState& state)
{
    while(true) {
        int x = rand() % 16;
        int y = rand() % 16;
        if (_grid[y][x] == element::VOID) {
            _fruitX = x;
            _fruitY = y;
            _grid[_fruitY][_fruitX] = element::APPLE;

            auto fruit = display->createRectangle();
            fruit->setHeight(_tileSize);
            fruit->setWidth(_tileSize);
            fruit->setPosX(_fruitX * _tileSize);
            fruit->setPosY(_fruitY * _tileSize);
            fruit->setColor(ARCADE::Color::Red);
            state.storeShape(std::move(fruit), "fruit");
            break;
        }
    }
}

void ARCADE::Snake::deleteSnake(ARCADE::GameState& state)
{
    for (std::size_t i = 0; i < _snake.size(); i++) {
        state.removeShape("snake_" + std::to_string(i));
    }

    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            if (x == 0 || x == 15 || y == 0 || y == 15) {
                state.removeShape("wall_" + std::to_string(x) + "_" + std::to_string(y));
            }
        }
    }
}