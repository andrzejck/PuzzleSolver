#include "puzzle.h"
#include "Segment.h"

Puzzle::Puzzle(const std::string & _id)
{
     id = std::string(_id);
     sidesIterable = 0;
     twoSided = false;
     area=0;
}



void Puzzle::addPoint(const Point& p){
     points.push_back(p);
     calculate();
}

unsigned long Puzzle::pointsCount() const {
     return points.size();
}

void Puzzle::calculate() {
     if(pointsCount() < 3)
          return;
     sides.clear();
     angles.clear();

     int i=0;
     unsigned long pc = pointsCount();
     minAngle=2*M_PI;
     for(int i=0; i < pointsCount(); i++){
          sides.push_back(points[i].distance(points[getCircularSideId(i+1)]));
          float angle = Segment(points[i], points[getCircularSideId(i+1)])
                             .angleBetween(Segment(points[i],points[getCircularSideId(i-1)]));
          if(angle < 0)
              angle = 2*M_PI+angle;
          if(angle < minAngle)
              minAngle = angle;
          angles.push_back(angle);
     }
     calculateArea();

}

int Puzzle::getSidesIterable() const {
     return sidesIterable;
}

void Puzzle::setSidesIterable(int sidesIterable) {
     Puzzle::sidesIterable = sidesIterable;
}

bool Puzzle::isTwoSided() const {
     return twoSided;
}

void Puzzle::setTwoSided(bool isTwoSided) {
     Puzzle::twoSided = isTwoSided;
}

Puzzle::Puzzle(const Puzzle &p) {
     id.assign(p.id);
     sidesIterable=p.sidesIterable;
     twoSided=p.twoSided;
     minSpan = p.minSpan;
     area=p.area;
     for(int i=0; i < p.pointsCount(); i++){
          points.push_back(p.points[i]);
          angles.push_back(p.sides[i]);
          sides.push_back(p.sides[i]);
     }
}

const std::string &Puzzle::getId() const {
     return id;
}

std::ostream& operator<<(std::ostream &strm, const Puzzle& p){
     strm << "Puzzle id [" << p.getId() << "] "<< std::endl;
     int i=0;
     for(auto it=p.begin(); it != p.end(); it++){
          strm << "   " << ((*it)) << " angle: "<< p.getAngle(i++) << std::endl;

     }
     return strm;
}

const float Puzzle::getSideLength(int pointId, int nextPointId) const {
     if ((pointId == pointsCount()-1) && (nextPointId ==0))
          return sides[pointId];

     if(pointId > nextPointId)
          return sides[nextPointId];
     else
          return sides[pointId];


}


float Puzzle::getAngle(int pointId) const{
     return angles[getCircularSideId(pointId)];
}

float Puzzle::getAngleToSegment(int pointId, int nextPointId, const Segment &s) const {

     int pointId_=getCircularSideId(pointId);
     int nextPointId_=getCircularSideId(nextPointId);

     /*if ((pointId_ == pointsCount()-1) && (nextPointId_ ==0))
          return s.angleBetween(Segment(points[pointId_], points[nextPointId_]));*/
     //if(pointId_ > nextPointId_)
     //     return s.angleBetween(Segment(points[nextPointId_], points[pointId_]));
     //else
          return s.angleBetween(Segment(points[pointId_], points[nextPointId_]));
}

const float Puzzle::getSideLengthS(int pointId, int nextPointId) const {
     return getSideLength(getCircularSideId(pointId), getCircularSideId(nextPointId));
}

void Puzzle::setId(const std::string &id) {
     Puzzle::id.assign(id);
}

void Puzzle::calculateArea() {
     area=0;
     int j =  pointsCount() - 1;
     for (int i = 0; i <  pointsCount(); i++)
     {
          area += (points[j].getX() + points[i].getX()) * (points[j].getY() - points[i].getY());
          j = i;  // j is previous vertex to i
     }
     area=abs(area/(2*10000));


}

float Puzzle::getArea() const {
     return area;
}

bool Puzzle::operator==(const Puzzle &rhs) const {
    return id.compare(rhs.id) == 0;
}

bool Puzzle::operator!=(const Puzzle &rhs) const {
    return !(rhs == *this);
}

float Puzzle::getMinSpan() const {
    return minSpan;
}

void Puzzle::setMinSpan(float minSpan) {
    Puzzle::minSpan = minSpan;
}

float Puzzle::getMinAngle() const {
    return minAngle;
}
