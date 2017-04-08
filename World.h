//
// Created by julian on 4/8/17.
//

#ifndef ENGINE_WORLD_H
#define ENGINE_WORLD_H


#include <vector>
#include "Entity.h"

class World {
public:
    World();

private:
    std::vector<Entity> entities;
};


#endif //ENGINE_WORLD_H
