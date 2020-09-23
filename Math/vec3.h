#pragma once

#include "..\global.h"

class vec3{
public:
    float val[3];

public:
    vec3() :val{0,0,0} {}    
    vec3(float v1, float v2, float v3) : val{v1, v2, v3} {}
    vec3(const vec3& rhs) : val{rhs.val[0], rhs.val[1], rhs.val[2]} {}

    float getX(){return val[0];}
    float getY(){return val[1];}
    float getZ(){return val[2];}

    float lengthSquared(){
        return val[0]*val[0] + val[1]*val[1] + val[2]*val[2];
    }

    float length(){
        return sqrt(lengthSquared());
    }

    vec3 operator-() const {return vec3(-val[0], -val[1], -val[2]);}
    float operator[](int i) const {return val[i];}
    float& operator[](int i) {return val[i];}
    vec3& operator+=(const vec3& rhs) {
        val[0] += rhs.val[0];
        val[1] += rhs.val[1];
        val[2] += rhs.val[2];
        return *this;
    }
    vec3& operator*=(const float& rhs) {
        val[0] *= rhs;  
        val[1] *= rhs;
        val[2] *= rhs;
        return *this;
    }
    friend vec3 operator+(const vec3& l, const vec3& r){
        return vec3(l.val[0] + r.val[0], l.val[1] + r.val[1], l.val[2] + r.val[2]);
    }
    friend vec3 operator-(const vec3& l, const vec3& r){
        return vec3(l.val[0] - r.val[0], l.val[1] - r.val[1], l.val[2] - r.val[2]);
    }
    friend vec3 operator*(const vec3& l, const float& r){
        return vec3(l.val[0]*r, l.val[1]*r, l.val[2]*r);
    }
    friend vec3 operator*(const float& l, const vec3& r){
        return r*l;
    }
    friend vec3 operator*(const vec3& l, const vec3& r){
        return vec3(l.val[0]*r.val[0], l.val[1]*r.val[1], l.val[2]*r.val[2]);
    }
    friend vec3 operator/(const vec3& l, const float& r){
        return l*(1/r);
    }
    friend float dot(const vec3& l, const vec3& r){
        return l.val[0]*r.val[0] + l.val[1]*r.val[1] + l.val[2]*r.val[2];
    }
    friend vec3 cross(const vec3&l, const vec3& r){
        return vec3(l.val[1]*r.val[2] - l.val[2]*r.val[1],
                    l.val[2]*r.val[0] - l.val[0]*r.val[2],
                    l.val[0]*r.val[1] - l.val[1]*r.val[0]); 
    }
    friend vec3 normalize(vec3 vec){
        return vec/vec.length();
    }
    
    inline static vec3 random(){
        return vec3(randomFloat(), randomFloat(), randomFloat());
    }
    inline static vec3 random(float min, float max){
        return vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
    }
};

vec3 randomInSphere(){
    auto a = randomFloat(0, 2 * Pi);
    auto z = randomFloat(-1, 1);
    auto r = sqrt(1 - z*z);
    return vec3(r*cos(a), r*sin(a), z);
}

vec3 reflect(const vec3& vec, const vec3& normal){
    return vec - 2*dot(vec, normal)*normal;
}

// refractRate n/n'
vec3 refract(const vec3& vec, const vec3& normal, float refractRate){
    auto cosa = dot(-vec, normal);
    vec3 rParallel = refractRate * (vec + cosa*normal);
    vec3 rPerp = -sqrt(1 - dot(rParallel, rParallel)) * normal;
    return rParallel + rPerp;
}

vec3 randomInDisk(){
    while(true){
        auto p = vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
        if(dot(p, p) >= 1)continue;
        return p;
    }
}