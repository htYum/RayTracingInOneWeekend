#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

using std::shared_ptr;
using std::make_shared;

const double Infinity = std::numeric_limits<double>::infinity();
const double Pi = 3.1415926535897932385;

inline float radians(float angle){
    return (angle * Pi)/180;
}

inline double ffmin(double a, double b){
    return a <= b ? a : b;
}

inline float ffmax(double a, double b){
    return a >= b ? a : b;
}

inline float randomFloat(){
    return rand()/(RAND_MAX + 1.0);
}

inline float randomFloat(float min, float max){
    return min + randomFloat() * (max - min);
}

inline float clamp(float x, float min, float max){
    if(x < min) return min;
    if(x > max) return max;
    return x;
}

inline float schlick(float cosine, float refIdx){
    float r0 = (1-refIdx)/(1+refIdx);
    r0 *= r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
}