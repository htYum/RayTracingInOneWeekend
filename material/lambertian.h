#pragma once

#include "material.h"

class lambertian : public material{
public:
    vec3 albedo;

public:
    lambertian(const vec3& a) : albedo(a){}

    virtual bool scatter(const ray& rayIn, const hitRecord& rec, vec3& attenuation, ray& scattered)const;
};

bool lambertian::scatter(const ray& rayIn, const hitRecord& rec, vec3& attenuation, ray& scattered)const{
    vec3 scatterDir = rec.normal + randomInSphere();
    scattered = ray(rec.p, scatterDir);
    attenuation = albedo;
    return true;
}