#pragma once

#include "Math/vec3.h"

class ray{
public:
    ray() = default;
    ray(const vec3& position, const vec3& direction):
        pos(position),
        dir(direction){}
    
    vec3 getPos() const {return pos;}
    vec3 getDir() const {return dir;}

    vec3 at(float t) const {
        return pos + t * dir;
    }

public:
    vec3 pos;
    vec3 dir;
};