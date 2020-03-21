#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#define ANG_DELTA (5.0/360.0*2*M_PI)
#define DIM_DELTA 10
#define DEG180 M_PI

class Point
{
private:
    float x;
    float y;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }
public:
    Point() { x=0.0; y=0.0;};
    explicit Point(float _x, float _y);
    Point(const Point &p2) {x = p2.x; y = p2.y; }
    float getX() const;
    void setX(float value);
    float getY() const;

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;

    void setY(float value);
    float distance(const Point& o) const;
    Point & operator + (const Point& o);
    //Point & operator + (Point& o);
    Point & operator - (const Point& o);
    friend std::ostream& operator<<(std::ostream &strm, const Point& p);

};



#endif // POINT_H
