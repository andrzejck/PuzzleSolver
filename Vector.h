//
// Created by ar on 15.03.20.
//

#ifndef PUZZLE_VECTOR_H
#define PUZZLE_VECTOR_H
#include "point.h"
#include <math.h>

class Vector {
private:
    float x;
    float y;
public:
    Vector(const Point & p){
        x=p.getX();
        y=p.getY();
    }
    Vector(float _x, float _y){
        x=_x;
        y=_y;
    }
    void normalize(){
        float len=sqrt(pow(x,2.0)+pow(y,2.0));
        if(len != 0) {
            x = x*(1/len);
            y = y*(1/len);
        }
    }

    void offset(float offset){
        x=x*offset;
        y=y*offset;
    }


    float getX() const {
        return x;
    }

    void setX(float x) {
        Vector::x = x;
    }

    float getY() const {
        return y;
    }

    void setY(float y) {
        Vector::y = y;
    }



};


#endif //PUZZLE_VECTOR_H
