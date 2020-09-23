#pragma once

#include "..\global.h"
#include "..\ray.h"
#include "..\object\object.h"

struct hitRecord;

class material{
public:
    virtual bool scatter(const ray& rayIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};