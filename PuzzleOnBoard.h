//
// Created by ar on 11.01.20.
//

#ifndef PUZZLE_PUZZLEONBOARD_H
#define PUZZLE_PUZZLEONBOARD_H

#include <memory>
#include "puzzle.h"
#include "Segment.h"
#include <QPointF>
#include <ostream>
#include "Polygon.h"

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>

class PuzzleOnBoard : public Polygon {
private:


    Puzzle  puzzle;
    Point centerPoint;
    int pivotPointId;
    float rotateAngle;
    bool isFlipped;


    std::vector<Point> points;
    std::vector<Segment> segments;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Polygon>(*this);
        ar & puzzle;
        ar & centerPoint;
        ar & pivotPointId;
        ar & rotateAngle;
        ar & isFlipped;
        ar & points;
        ar & segments;

    }

public:
    PuzzleOnBoard() {};
    PuzzleOnBoard(const Puzzle &_puzzle,
                  const Point & _centerPoint = Point(0,0),
                  float _rotateAngle = 0,
                  bool _isFlipped = false,
                  int _pivotPointId = 0);

    PuzzleOnBoard(const PuzzleOnBoard & p);
    const Point &getCenterPoint() const;
    void setCenterPoint(const Point &centerPoint);
    int getPointId() const;
    void setPointId(int pointId);
    float getRotateAngle() const;
    void setRotateAngle(float rotateAngle);
    bool getFlipped() const;
    const float getArea() const {return puzzle.getArea();}
    auto begin() const{
        return puzzle.begin();
    }

    const int inside(const Point & p) const;

    auto end() const{
        return puzzle.end();
    }

    float getAngleToSegment(int pointId, int nextPointId, const Segment & s) const {
        //if(isFlipped)
        //    return puzzle.getAngleToSegment(nextPointId,pointId, s) + rotateAngle;
        //else
        if( isFlipped) // && pointId == 0)
                return puzzle.getAngleToSegment(pointId, nextPointId, s) + rotateAngle - M_PI;
            else
                return puzzle.getAngleToSegment(pointId, nextPointId, s) + rotateAngle;
    }
    float getAngle(int pointId) const{
        //int pointId_=Puzzle::getCircularSideId(pointId,pointsCount())
        return puzzle.getAngle(pointId);
    }

    float getSideLength(int pointId, int nextPointId) const {
        return puzzle.getSideLength(pointId, nextPointId);
    }

    float getSideLengthS(int pointId, int nextPointId) const {
        return puzzle.getSideLength(Puzzle::getCircularSideId(pointId, puzzle.pointsCount()),
                                    Puzzle::getCircularSideId(nextPointId, puzzle.pointsCount()));
    }

    const Point & get(int pointId) const{
        int pointId_=Puzzle::getCircularSideId(pointId,pointsCount());
        return points[pointId_];
    }



    unsigned long pointsCount() const{
        return points.size();
    }
    /*QPointF * asQPointF(){
        QPointF * res=new QPointF[puzzle.pointsCount()];
        int i=0;
        for(auto it=puzzle.begin(); it != puzzle.end(); it++){
            QPointF * qPointF = new QPointF((*(*it)).getX(), (*it)->getY());
            res[i++]=*qPointF;
        }
        return res;
    }*/

    const std::string & getId() const {

        return puzzle.getId();
    }

    friend std::ostream &operator<<(std::ostream &os, const PuzzleOnBoard &board);

    void calculate();
    PuzzleOnBoard & translate(const Point & vector);
    PuzzleOnBoard & rotate(float angle, int pointId);
    PuzzleOnBoard & scale(float scale);
    PuzzleOnBoard & reset();
    PuzzleOnBoard & flip();

    PuzzleOnBoard & operator=(const PuzzleOnBoard & other);

    QPointF * asQPointF(float scale, float ox, float oy){
        QPointF * res=new QPointF[points.size()];
        int i=0;
        for(auto it=points.begin(); it != points.end(); it++){
            QPointF * qPointF = new QPointF((*it).getX()*scale+ox, (*it).getY()*scale+oy);
            res[i++]=*qPointF;
        }
        return res;
    }


    bool isIsFlipped() const;





};


#endif //PUZZLE_PUZZLEONBOARD_H
