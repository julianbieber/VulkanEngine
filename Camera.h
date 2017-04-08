//
// Created by julian on 4/8/17.
//

#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H


#include <vector>
#include "Entity.h"

class Camera : public Entity {
public:
    Camera();
    // render(const std::vector<Drawable>& drawables);
private:
    float horizontalFowAngle;
    float verticalFowAngle;
};


#endif //ENGINE_CAMERA_H
