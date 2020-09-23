#pragma once

#include <vector>
#include "object.h"
#include "..\global.h"

class objectList : public object{
public:
    objectList(){}
    objectList(shared_ptr<object> obj) {add(obj);} 
    ~objectList(){}
    void add(shared_ptr<object> obj){
        objects.push_back(obj);
    }
    void clear(){
        objects.clear();
    }
    
    virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;

public:
    std::vector<shared_ptr<object> > objects;
};

bool objectList::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const{
    hitRecord tempRec;
    bool hitOne = false;
    float far = tMax;

    for(const auto& obj : objects){
        if(obj->hit(r, tMin, far, tempRec)){
            hitOne = true;
            far = tempRec.t;
            rec = tempRec;
        }
    }
    return hitOne;
}