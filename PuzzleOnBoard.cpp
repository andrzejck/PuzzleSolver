//
// Created by ar on 11.01.20.
//

#include "PuzzleOnBoard.h"
#include <cmath>

PuzzleOnBoard::PuzzleOnBoard(const Puzzle  * _puzzle,
                             const Point & _centerPoint ,
                             float _rotateAngle ,
                             bool _isFlipped ,
                             int _pivotPointId) : puzzle(_puzzle) {
    puzzle = _puzzle;
    puzzleId.assign(puzzle->getId());
    reset();
    rotateAngle = _rotateAngle;
    centerPoint =  Point(_centerPoint);
    pivotPointId = _pivotPointId;
    isFlipped = _isFlipped;

    setColor(Qt::black);

}

const Point &PuzzleOnBoard::getCenterPoint() const {
    return centerPoint;
}

void PuzzleOnBoard::setCenterPoint(const Point &centerPoint) {
    PuzzleOnBoard::centerPoint = centerPoint;
}

int PuzzleOnBoard::getPointId() const {
    return pivotPointId;
}

void PuzzleOnBoard::setPointId(int pointId) {
    PuzzleOnBoard::pivotPointId = pointId;
}

float PuzzleOnBoard::getRotateAngle() const {
    return rotateAngle;
}

void PuzzleOnBoard::setRotateAngle(float rotateAngle) {
    PuzzleOnBoard::rotateAngle = rotateAngle;
}

bool PuzzleOnBoard::getFlipped() const {
    return isFlipped;
}



void PuzzleOnBoard::calculate(){
    /*isCalculated=true;
    if(! isFlipped){
        auto pivotPoint = std::make_shared<Point>(points[pivotPointId]);
    }*/
}
PuzzleOnBoard & PuzzleOnBoard::flip(){
    isFlipped = true;
    points.clear();
    segments.clear();
    float maxX=0;
    for(auto p = puzzle->begin(); p!=puzzle->end(); p++){

        if  ( p->getX() > maxX) {
            maxX = p->getX();
        }
        points.push_back(Point(-(p->getX()),p->getY())+centerPoint);
    }
    for(Point p: points){
        p.setX(p.getX()+maxX);
    }
    return *this;
}

PuzzleOnBoard &PuzzleOnBoard::translate(const Point &vector) {
    Point pivotPoint=points[pivotPointId];
    for(int i = 0; i < points.size(); i++){
        points[i]=points[i]+vector-pivotPoint;
        //points[i]=points[i]-points[pivotPointId];
    }
    centerPoint = vector;
    return *this;
}

PuzzleOnBoard &PuzzleOnBoard::rotate(float angle, int pointId) {
    Point & pivot = points[pointId];
    pivotPointId = pointId;
    float xp=pivot.getX();
    float yp=pivot.getY();
    float x0=centerPoint.getX();
    float y0=centerPoint.getY();
    float x_shifted, y_shifted;
    for(int i=0; i < points.size(); i++){
        x_shifted=points[i].getX()-xp;
        y_shifted=points[i].getY()-yp;
        points[i].setX(xp+x_shifted*cos(angle) - y_shifted*sin(angle));
        points[i].setY(yp+x_shifted*sin(angle) + y_shifted*cos(angle));

    }
    rotateAngle = angle;
    return *this;


}

PuzzleOnBoard &PuzzleOnBoard::reset() {
    if(puzzle == nullptr)
        throw std::logic_error("reset when puzzle is null");
    points.clear();
    isFlipped=false;
    centerPoint=Point(0,0);
    rotateAngle=0;
    for(auto it = puzzle->begin(); it != puzzle->end(); it++){
        points.push_back(*it);
    }

    return *this;

}

PuzzleOnBoard &PuzzleOnBoard::operator=(const PuzzleOnBoard & other) {
    points.clear();
    for(auto it = other.points.begin(); it != other.points.end(); it++){
        points.push_back(((*it)));
    }
    return *this;

}

std::ostream &operator<<(std::ostream &os, const PuzzleOnBoard &board) {

    os << "Puzzle on board id [" << /*board.getId() << */ "] "<< std::endl;
    for(auto it=board.points.begin(); it != board.points.end(); it++){
        os << "   " << (*it) << std::endl;

    }
    return os;
}

bool PuzzleOnBoard::isIsFlipped() const {
    return isFlipped;
}

PuzzleOnBoard::PuzzleOnBoard(const PuzzleOnBoard &p){
    puzzle=p.puzzle;
    puzzleId.assign(puzzle->getId());
    centerPoint = p.centerPoint;

    pivotPointId = p.pivotPointId;
    rotateAngle = p.rotateAngle;
    isFlipped = p.isFlipped;


    points = p.points;
    segments = p.segments;


}

PuzzleOnBoard &PuzzleOnBoard::scale(float scale){
    for(int i = 0; i < points.size(); i++){
        points[i].setX(points[i].getX()*scale);
        points[i].setY(points[i].getY()*scale);
        //puzzle.scaleAngle(i,scale);
        //puzzle->scaleSide(i,scale);

    }
    return *this;
}

const int PuzzleOnBoard::inside(const Point & p) const{
    int wn = 0;
    Segment tmpSeg;
    for(int i=0; i < pointsCount(); i++){
        tmpSeg=Segment(get(i), get(i+1));
        if(get(i).getY() <= p.getY()){
            if(get(i+1).getY() > p.getY()){
                if(tmpSeg.isLeft(p) > 0){
                    wn++;
                }
            }
        } else {
            if (get(i + 1).getY() <= p.getY()) {
                if (tmpSeg.isLeft(p) < 0){
                    wn--;
                }
            }

        }
    }
    return wn;

}