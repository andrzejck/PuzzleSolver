//
// Created by ar on 14.01.20.
//

#ifndef PUZZLE_POINTOFENVELOPE_H
#define PUZZLE_POINTOFENVELOPE_H


#include <ostream>
#include "point.h"
#include "Segment.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class PointOfEnvelope: public Point {
private:
    float angle;
    bool adjacentTuPuzzle = false;


    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Point>(*this);
        ar & angle;
        ar & adjacentTuPuzzle;
    }

public:
    bool isAdjacentTuPuzzle() const {
        return adjacentTuPuzzle;
    }

    void setAdjacentTuPuzzle(bool notAdjacentTuPuzzle) {
        PointOfEnvelope::adjacentTuPuzzle = notAdjacentTuPuzzle;
    }
    PointOfEnvelope(const Point & p){
        setX(p.getX());
        setY(p.getY());
        angle = 0;
        adjacentTuPuzzle = false;
    }

    PointOfEnvelope(){
        setX(0);
        setY(0);
        angle = 0;
        adjacentTuPuzzle = false;

    }
public:
    friend std::ostream &operator<<(std::ostream &os, const PointOfEnvelope &envelope) {
        os << static_cast<const Point &>(envelope) << " angle: " << envelope.angle;
        return os;
    }

    using Point::Point;
    float calcAngle(const Point & prev, const Point & next){
        angle = Segment(static_cast<Point>(*this), next).angleBetween(Segment(static_cast<Point>(*this), prev));
        return angle;
    }

    float getAngle() const {return angle;}

    void setAngle(float _angle) {angle=_angle;}

};


#endif //PUZZLE_POINTOFENVELOPE_H
