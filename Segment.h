//
// Created by ar on 11.01.20.
//

#ifndef PUZZLE_SEGMENT_H
#define PUZZLE_SEGMENT_H


#include "point.h"
//#include "PointOfEnvelope.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>



class Segment {
private:
    Point A;
    Point B;
    float vectorProduct(Point x, Point y, Point z);
    float length;
    float angleTo0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & A;
        ar & B;
        ar & length;
        ar & angleTo0;
    }
public:
    Segment() {};
    Segment(float xa, float ya, float xb, float yb);
    Segment(const Point & a, const Point & b);
  //  Segment(const PointOfEnvelope & a, const PointOfEnvelope & b);
    float getLength();
    float angleBetween(const Segment & other) const;
    bool inters(const Segment & other);
    bool inters2(const Segment &other);
    bool intersStrong(const Segment & other);
    Point findIntersectionOfLines(const Segment & other);
    bool isParallel(const Segment & other, float precision);
    float distanceToPoint(const Point & p) const;
    const bool pointOnSegment(const Point & q) const;
    Point pointOnSegmentDistanceToA(float distance);
    int isLeft(const Point & p){
        return ( (B.getX() - A.getX()) * (p.getY() - A.getY())
                 - (p.getX() -  A.getX()) * (B.getY() - A.getY()));
    }


};

extern Segment SEGMENT0;

#endif //PUZZLE_SEGMENT_H
