//
// Created by julian on 4/8/17.
//

#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H


#include "Window.h"
#include "Graphics.h"

class Game {
public:
    Game();
    void run();

private:
    Window window;
    Graphics graphics;
};


#endif //ENGINE_GAME_H
