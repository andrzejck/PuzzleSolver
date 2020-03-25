#ifndef PUZZLE_H
#define PUZZLE_H
#include <vector>
#include <memory>
#include <math.h>
#include <iostream>
#include <QPointF>
#include <functional>
#include <string>
#include <fstream>


#include "point.h"
#include "Segment.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

/*
 *    0 __0__ 1
 *     |     |
 *    3|     |1
 *     |_____|
 *    3   2   2
 *
 *
 */
class Puzzle
{

private:
    std::vector<Point> points;
    std::vector<float> sides;
    std::vector<float> angles;
    std::string id;
    float area;
    int sidesIterable;
    bool twoSided;
    float minSpan;
    float minAngle;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & points;
        ar & sides;
        ar & angles;
        ar & id;
        ar & area;
        ar & sidesIterable;
        ar & twoSided;
        ar & minSpan;
        ar & minAngle;

    }

public:
    float getMinAngle() const;

public:
    float getMinSpan() const;

    void setMinSpan(float minSpan);

public:
    float getArea() const;
    const std::string &getId() const;
    int getSidesIterable() const;
    void setSidesIterable(int sidesIterable);
    bool isTwoSided() const;
    void setId(const std::string &id);
    void setTwoSided(bool isTwoSided);
    void calculateArea();
    void clear(){
        points.clear();
        sides.clear();
        angles.clear();
        id="";
    }

public:
    //constexpr static const float DEG180=M_PI;
    Puzzle(){
        Puzzle(std::string(""));
    }
    Puzzle(const std::string & _id);
    Puzzle(const Puzzle & p);
    void addPoint(const Point& p);
    unsigned long pointsCount() const;

    bool operator==(const Puzzle &rhs) const;

    bool operator!=(const Puzzle &rhs) const;

    void calculate();

    float getAngleToSegment(int pointId, int nextPointId, const Segment & s) const;
    const float getSideLength(int pointId, int nextPointId) const;
    const float getSideLengthS(int pointId, int nextPointId) const;
    float scaleSide(int sideId, float scale){
        sides[sideId]=sides[sideId]*scale;
    }
    float scaleAngle(int angleId, float scale){
        angles[angleId]=angles[angleId]*scale;
    }

    float getAngle(int pointId) const;
    static int getCircularSideId(int side, int sidesCount){
        return ((side)%sidesCount+sidesCount)%sidesCount;
    }

    auto begin() const{
        return points.begin();
    }

    auto end() const{
        return points.end();
    }

    const int getCircularSideId(int side) const{
        return getCircularSideId(side, pointsCount());
    }

    QPointF * asQPointF(float scale, float ox, float oy){
        QPointF * res=new QPointF[pointsCount()];
        int i=0;
        for(auto it=begin(); it != end(); it++){
            QPointF * qPointF = new QPointF((*it).getX()*scale+ox, (*it).getY()*scale+oy);
            res[i++]=*qPointF;
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream &strm, const Puzzle& p);
   //{
   //     points.push_back(std::make_unique<Point>(point));
   // }
   float getAngleToSegment(int pointId, int nextPointId, const Segment & s, bool isFlipped) const {

       if( isFlipped)
           return getAngleToSegment(pointId, nextPointId, s)  - M_PI;
       else
           return getAngleToSegment(pointId, nextPointId, s);
   }

};

class PuzzleHashFunction {
public:

    size_t operator()(const Puzzle& l) const
    {
        return std::hash<std::string>{}(l.getId());
    }
};

#endif // PUZZLE_H
