#pragma once

#include "global.h"
#include "ray.h"

class camera{
public:
    camera(const vec3& cameraPos, const vec3& target, const vec3& worldUp, float fov, double scale, float aperture, float focusDistance){
        pos = cameraPos;
        lensRadius = aperture / 2;

        float a = radians(fov);
        float halfHeight = tan(a/2);
        float halfWidth = scale * halfHeight;
        z = normalize(cameraPos - target);
        x = normalize(cross(worldUp, z));
        y = cross(z, x);

        leftDown = pos - focusDistance*(halfWidth * x + halfHeight * y + z);
        horizontal = 2 * halfWidth * x * focusDistance;
        vertical = 2 * halfHeight * y * focusDistance;
    }
    ~camera(){}

    ray getRay(float u, float v){
        vec3 rd = lensRadius * randomInDisk();
        vec3 offset = x*rd.getX() + y*rd.getY();
        return ray(pos + offset, leftDown + u * horizontal + v * vertical - pos - offset);
    }

public:
    vec3 pos;
    vec3 leftDown;
    vec3 horizontal;
    vec3 vertical;
    vec3 x;
    vec3 y;
    vec3 z;
    float lensRadius;
};