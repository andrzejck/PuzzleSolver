#include "point.h"
#include <math.h>

float Point::getX() const
{
    return x;
}

void Point::setX(float value)
{
    x = value;
}

float Point::getY() const
{
    return y;
}

void Point::setY(float value)
{
    y = value;
}

Point::Point(float _x, float _y)
{
    x=_x;
    y=_y;
}

float Point::distance(const Point& o) const{
    return sqrt((o.x-x)*(o.x-x)+(o.y-y)*(o.y-y));
}


std::ostream& operator<<(std::ostream &strm, const Point& p){
    strm << "(" << p.getX() << "," << p.getY() << ")";
    return strm;
}

Point & Point::operator+(const Point &o) {
    x=x+o.x;
    y=y+o.y;
    return *this;
}



Point & Point::operator-(const Point &o) {
    x=x-o.x;
    y=y-o.y;
    return *this;

}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}