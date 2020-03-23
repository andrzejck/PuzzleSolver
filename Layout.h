//
// Created by ar on 13.01.20.
//

#ifndef PUZZLE_LAYOUT_H
#define PUZZLE_LAYOUT_H
#include <vector>
#include <ostream>
#include "PuzzleOnBoard.h"
#include "PointOfEnvelope.h"
#include "point.h"
#include "PuzzleList.h"
#include <stack>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>




#define BOARDSIZE 1043
#define MARGIN 10

enum Fit {ok=1, angle=-1, length=-2, outOfBoard=-3, inters=-4};
#define CIR(x,y) Puzzle::getCircularSideId(x,y)

class Layout : public Polygon {
public:

private:
   std::vector<PuzzleOnBoard> puzzlesOnBoard;
   std::vector<PointOfEnvelope> envelope;
   std::vector<PointOfEnvelope> envelopeEnlarged;
   std::vector<float> envelopeSides;
   void calculateAngles();
   std::stack<int> envelopePointsToVisit;
   std::stack<int> puzzlePointsToVisit;
   float sumArea=0;
   float sumEnvelope=0;
   float angleSumm = 0;
   int fgOrigin = 0;
   float minSide = 0;
   float qualityFactor = 0;
   int puzzlesCountTrace=-1;
public:
    float getQualityFactor() const;

public:
    float getMinSide() const;

public:
    int getFgOrigin() const;
    void setFgOrigin(int fgOrigin);
    const bool isPromissing(float minAngle, float minSpan) const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Polygon>(*this);
        ar & puzzlesOnBoard;
        ar & envelope;
        ar & envelopeSides;
        ar & sumArea;
        ar & sumEnvelope;
        ar & fgOrigin;
        ar & minSide;
        ar & envelopeEnlarged;

    }

public:
    float getSumEnvelope() const;
    /*~Layout(){
        //std::cout << "~L" << std::endl;
        ;
    }*/

    bool operator==(const Layout &rhs) const;




    bool operator!=(const Layout &rhs) const;

    float getSumArea() const;;
    bool insert(int pos, const PointOfEnvelope  &p);
    void push_back(const PointOfEnvelope &p);
    void erase(int p);
    const PointOfEnvelope & next(int p) const;
    const PointOfEnvelope & prev(int p) const;
    const PointOfEnvelope & get(int i) const;
    const PointOfEnvelope & getE(int i) const;
    const std::vector<PuzzleOnBoard>& getPuzzles() const {
        return puzzlesOnBoard;
    }

    void insertPuzzleOnBoard(const PuzzleOnBoard p){
        puzzlesOnBoard.push_back(p);
    }

    float getAngleToSegment(int pointId, int nextPointId, const Segment & s) const;

    std::vector<PointOfEnvelope>::const_iterator cbegin(){
        return envelope.cbegin();
    }

    std::vector<PointOfEnvelope>::const_iterator cend(){
        return envelope.cend();
    }

    bool doesPuzzleFit(const PuzzleOnBoard &puzzle,
                       int layoutPointId,
                       int layoutNextPointId,
                       int puzzlePointId,
                       int puzzleNextPointId,
                       bool flipped) const;

    bool hasLoop();


    friend std::ostream &operator<<(std::ostream &os, const Layout &layout);

    QPointF * asQPointF(float scale, float ox, float oy){
        QPointF * res=new QPointF[envelope.size()];
        int i=0;
        for(auto it=envelope.begin(); it != envelope.end(); it++){
            QPointF * qPointF = new QPointF((*it).getX()*scale+ox, (*it).getY()*scale+oy);
            res[i++]=*qPointF;
        }
        return res;
    }

    QPointF * asQPointFEnlarged(float scale, float ox, float oy){
        QPointF * res=new QPointF[envelope.size()];
        int i=0;
        for(auto it=envelopeEnlarged.begin(); it != envelopeEnlarged.end(); it++){
            QPointF * qPointF = new QPointF((*it).getX()*scale+ox, (*it).getY()*scale+oy);
            res[i++]=*qPointF;
        }
        return res;
    }

    unsigned long pointsCount() const{
        return envelope.size();
    }

    unsigned long puzzleCount() const{
        if(puzzlesCountTrace == -1)
            return puzzlesOnBoard.size();
        else
            return puzzlesCountTrace;
    }

    void clearPuzzleList(){
        puzzlesCountTrace=puzzlesOnBoard.size();
        puzzlesOnBoard.clear();
        puzzlesOnBoard.shrink_to_fit();
    }

    static int compareAng(float a, float b){
        if (abs(a-b) <= ANG_DELTA) return 0;
        if (a < b)
            return -1;
        else
            return 1;
    }

    static int compareDim(float a, float b){
        if (abs(a-b) <= DIM_DELTA) return 0;
        if (a < b)
            return -1;
        else
            return 1;
    }

    float getSideLengthS(int pointId, int nextPointId) const;

    float getAngle(int pointId) const;



    float requiredRotateAngle(const Puzzle & puzzle,
                            int layoutPointId,
                            int layoutNextPointId,
                            int puzzlePointId,
                            int puzzleNextPointId) const;

    void modifyEnvelope(const PuzzleOnBoard & puzzleOnBoard,
                          int layoutPointId,
                          int layoutNextPointId,
                          int puzzlePointId,
                          int puzzleNextPointId);
    bool isAdjacentToPuzzle(int i){
        return envelope[i].isAdjacentTuPuzzle();
    }
    void setAdjacentToPuzzle(int i, bool adjacent){
        envelope[i].setAdjacentTuPuzzle(adjacent);
    }

    bool checkInterlaceWithPuzzles(const std::string & msg);

    int n(int i){
        return CIR(i+1, envelope.size());
    }

    const int inside(const Point &p) const;

    const float anglesSum() const{
        return angleSumm;
/*        float sum=0;
        for (auto e: envelope){
            sum = (int)(((e.getAngle()*360)/2*M_PI)/5)*5;
        }*/
    }
    void generateEnlarged(float offset);
};

class LayoutHashFunction {
public:

    // Use sum of lengths of first and last names
    // as hash function.
    size_t operator()(const Layout& l) const
    {
        return l.getSumArea()+l.getSumEnvelope()+l.pointsCount()+l.puzzleCount();
    }
};





#endif //PUZZLE_LAYOUT_H
