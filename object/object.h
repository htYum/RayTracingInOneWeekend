#pragma once

#include "..\ray.h"
#include "..\material\material.h"

struct hitRecord{
    vec3 p;
    vec3 normal;
    shared_ptr<material> mat;
    float t;
    bool frontFace;

    inline void setFaceNormal(const ray& r, const vec3& outwardNormal){
        frontFace = dot(r.getDir(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class object{
public:
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const = 0;
};