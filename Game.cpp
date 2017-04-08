//
// Created by julian on 4/8/17.
//

#include <iostream>
#include "Game.h"

Game::Game() : window(800, 600), graphics(window) {

}

void Game::run() {
    std::cout << "run" << std::endl;
    while (!window.shouldClose()) {
        window.processWindowEvents();
    }
}