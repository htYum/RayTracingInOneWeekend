#pragma once

#include "material.h"

class matel : public material{
public:
    vec3 albedo;
    float fuzz;

public:
    matel(){}
    matel(const vec3& a, float f) : 
        albedo(a),
        fuzz(f){}
    ~matel(){}

    virtual bool scatter(const ray& rayIn, const hitRecord& rec, vec3& attenuation, ray& scattered)const;
};

bool matel::scatter(const ray& rayIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const{
    vec3 reflected = reflect(normalize(rayIn.getDir()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * randomInSphere());
    attenuation = albedo;
    return (dot(rec.normal, reflected) > 0);
}