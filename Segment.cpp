//
// Created by ar on 11.01.20.
//

#include "Segment.h"
#include <math.h>
#include <Math.h>
#include "puzzle.h"



Segment SEGMENT0 = Segment(0.0, 0.0, 1000, 0);

//SEGMENT0 = Segment(0.0, 0.0, 1000, 0);

Segment::Segment(float xa, float ya, float xb, float yb) {
    A=Point{xa, ya};
    B=Point{xb, yb};
    length=A.distance(B);
    angleTo0 = SEGMENT0.angleBetween(*this);

}

Segment::Segment(const Point &a, const Point &b) {
    A = Point(a);
    B = Point(b);
    length=A.distance(B);
    angleTo0 = SEGMENT0.angleBetween(*this);
}

/*Segment::Segment(const PointOfEnvelope &a, const PointOfEnvelope &b) {
    A = Point(a);
    B = Point(b);
    length=A.distance(B);
    angleTo0 = SEGMENT0.angleBetween(*this);
}*/

float Segment::getLength(){
    return length;
}

float Segment::angleBetween(const Segment &other) const {
    short x1=B.getX()-A.getX();
    //float x2=other.B.getX()-A.getX();
    short x2=other.B.getX()-other.A.getX();
    short y1=B.getY()-A.getY();

    //float y2=other.B.getY()-A.getY();
    short y2=other.B.getY()-other.A.getY();

    int dot = x1*x2 + y1*y2;//      # dot product between [x1, y1] and [x2, y2]
    int det = x1*y2 - y1*x2;//      # determinant
    float alfa = Math::ApproxAtan2(det, dot);
    return alfa;

}

float Segment::vectorProduct(Point x, Point y, Point z) {
    float x1=z.getX()-x.getX();
    float y1=z.getY()-x.getY();
    float x2=y.getX()-x.getX();
    float y2=y.getY()-x.getY();
    return x1*y2-x2*y1;
}



bool Segment::inters(const Segment &other) {


    /*float ang=angleBetween(other);
    if ((abs(ang) < ANG_DELTA/4) || (abs(abs(ang)-DEG180) < ANG_DELTA/4))
        return false;*/

    float v1=vectorProduct(other.A,other.B,A);
    float v2=vectorProduct(other.A,other.B,B);
    float v3=vectorProduct(A,B,other.A);
    float v4=vectorProduct(A,B,other.B);

    if(((v1>0&&v2<0)||(v1<0&&v2>0))&&((v3>0&&v4<0)||(v3<0&&v4>0)))
        return true;
    else {
        return false;
//        if(pointOnSegment(other.A) ||
//            pointOnSegment(other.B) ||
//            other.pointOnSegment(A) ||
//            other.pointOnSegment(B))
//            return true;
//        else
//            return false;
//
//        return false;
//        if(pointOnSegment(other.A) && ((A.distance(other.A) > DIM_DELTA) || ((B.distance(other.A) > DIM_DELTA)) ))
//            return true;
//
//        if(pointOnSegment(other.B) && ((A.distance(other.B) > DIM_DELTA) || ((B.distance(other.B) > DIM_DELTA)) ))
//            return true;
//
//        if(other.pointOnSegment(A) && ((other.A.distance(A) > DIM_DELTA) || ((other.B.distance(A) > DIM_DELTA)) ))
//            return true;
//
//        if(other.pointOnSegment(B) && ((other.A.distance(B) > DIM_DELTA) || ((other.B.distance(B) > DIM_DELTA)) ))
//            return true;

    }
}





bool Segment::isParallel(const Segment &other, float precision) {
    //Segment x1=
    Segment x1=Segment(Point(0,0), Point(B.getX()-A.getX(),
                                                     B.getY()-A.getY()));
    Segment x2=Segment(Point(0,0), Point(other.B.getX()-other.A.getX(),
                                                     other.B.getY()-other.A.getY()));

    float angleBetween=x1.angleBetween(x2);
    return (abs(angleBetween) < precision) || (abs(abs(angleBetween)-DEG180) < precision);
}

/*
 * pDistance(x, y, x1, y1, x2, y2) {

  var A = x - x1;
  var B = y - y1;
  var C = x2 - x1;
  var D = y2 - y1;

  var dot = A * C + B * D;
  var len_sq = C * C + D * D;
  var param = -1;
  if (len_sq != 0) //in case of 0 length line
      param = dot / len_sq;

  var xx, yy;

  if (param < 0) {
    xx = x1;
    yy = y1;
  }
  else if (param > 1) {
    xx = x2;
    yy = y2;
  }
  else {
    xx = x1 + param * C;
    yy = y1 + param * D;
  }

  var dx = x - xx;
  var dy = y - yy;
  return Math.sqrt(dx * dx + dy * dy);
}
 */
float Segment::distanceToPoint(const Point &p) const {
    float A=p.getX()-Segment::A.getX();
    float B=p.getY()-Segment::A.getY();
    float C=Segment::B.getX()-Segment::A.getX();
    float D=Segment::B.getY()-Segment::A.getY();
    float dot = A * C + B * D;
    float len_sq = C * C + D * D;
    float param = -1;
    if (len_sq != 0) //in case of 0 length line
        param = dot / len_sq;

    float xx,yy;

    if (param < 0) {
        xx = Segment::A.getX();
        yy = Segment::A.getY();
    }
    else if (param > 1) {
        xx = Segment::B.getX();
        yy = Segment::B.getY();
    }
    else {
        xx = Segment::A.getX() + param * C;
        yy = Segment::A.getY() + param * D;
    }
    float dx=p.getX()-xx;
    float dy=p.getY()-yy;

    return sqrt(dx*dx+dy*dy);

}

bool Segment::inters2(const Segment &other){
    // intresects but no equivalent
    if (((A == other.A) && (B == other.B)) ||
            ((A == other.B) &&  (B == other.A)))
        return false;

    if( distanceToPoint(other.A) < 2*DIM_DELTA ||
        distanceToPoint(other.B) < 2*DIM_DELTA ||
        other.distanceToPoint(A) < 2*DIM_DELTA ||
        other.distanceToPoint(B) < 2*DIM_DELTA){
        return false;
    }
    return inters(other);

}

bool Segment::intersStrong(const Segment &other) {




    float v1=vectorProduct(other.A,other.B,A);
    float v2=vectorProduct(other.A,other.B,B);
    float v3=vectorProduct(A,B,other.A);
    float v4=vectorProduct(A,B,other.B);

    if(((v1>0&&v2<0)||(v1<0&&v2>0))&&((v3>0&&v4<0)||(v3<0&&v4>0)))
        return true;
    else {
        return false;
//        if(pointOnSegment(other.A) ||
//            pointOnSegment(other.B) ||
//            other.pointOnSegment(A) ||
//            other.pointOnSegment(B))
//            return true;
//        else
//            return false;
//
//        return false;
//        if(pointOnSegment(other.A) && ((A.distance(other.A) > DIM_DELTA) || ((B.distance(other.A) > DIM_DELTA)) ))
//            return true;
//
//        if(pointOnSegment(other.B) && ((A.distance(other.B) > DIM_DELTA) || ((B.distance(other.B) > DIM_DELTA)) ))
//            return true;
//
//        if(other.pointOnSegment(A) && ((other.A.distance(A) > DIM_DELTA) || ((other.B.distance(A) > DIM_DELTA)) ))
//            return true;
//
//        if(other.pointOnSegment(B) && ((other.A.distance(B) > DIM_DELTA) || ((other.B.distance(B) > DIM_DELTA)) ))
//            return true;

    }


}

Point Segment::pointOnSegmentDistanceToA(float distance) {
    float t=distance/length;
    return Point((1-t)*A.getX()+t*B.getX(),
                 (1-t)*A.getY()+t*B.getY());
}

/*Segment::Segment(const PointOfEnvelope &a, const PointOfEnvelope &b) {
    Segment(std::static_cast<Point> a, std::static_cast<Point> b);

}*/

const bool Segment::pointOnSegment(const Point & q) const {
    if  (((q.getY() - A.getY()) * (B.getX() - q.getX()) -
              (q.getX() - A.getX()) * (B.getY() - q.getY())) == 0) {
        if (q.getX() <= std::max(A.getX(), B.getX()) && q.getX() >= std::min(A.getX(), B.getX()) &&
            q.getY() <= std::max(A.getY(), B.getY()) && q.getY() >= std::min(A.getY(), B.getY()))
            return true;
        else
            return false;
    } else
        return false;
}

Point Segment::findIntersectionOfLines(const Segment &other) {
    float dx12 = B.getX() - A.getX();
    float dy12 = B.getY() - A.getY();
    float dx34 = other.B.getX() - other.A.getX();
    float dy34 = other.B.getY() - other.A.getY();
    float denominator = (dy12 * dx34 - dx12 * dy34);
    if(denominator == 0)
        return Point(NAN, NAN);
    float t1 =
            ((A.getX() - other.A.getX()) * dy34 + (other.A.getY() - A.getY()) * dx34)
            / denominator;
/*    float t2 =
            ((other.A.getX() - A.getX()) * dy12 + (A.getY() - other.A.getY()) * dx12)
            / -denominator;*/
    return Point(A.getX() + dx12 * t1, A.getY() + dy12 * t1);
}
