//
// Created by ar on 13.01.20.
//

#include "Layout.h"
#include <map>
#include <unordered_map>

#include <stdexcept>
#include "Vector.h"

#define SIMPLIFY
#define COUT(x) std::cout << x << std::endl;
//#define COUT1(x) std::cout << x << std::endl;
#define COUT1(x) ;
#define CHECKLINESINTERLACE


bool Layout::insert(int pos, const PointOfEnvelope &p) {
    /*if ((next(pos).distance(p) < DIM_DELTA) || (prev(pos).distance(p) < DIM_DELTA))
//        int i=1;
       return false;
    if (pos > envelope.size() ) {
        throw std::range_error("pos is bigger than envelope size%d, %d ");
    }*/

    envelope.insert(envelope.begin()+pos, p);
    //envelopeSides.insert(envelopeSides.begin()+pos, 0);
    //envelopeSides.push_back(0);
    //calculateAngles();
    //envelopePointsFromPuzzle.insert(std::make_pair<int,int>(pos, i));
    return true;

}

void Layout::push_back(const PointOfEnvelope &p) {
    envelope.push_back(p);
//    envelopeSides.push_back(0);
    calculateAngles();
}

const PointOfEnvelope &Layout::next(int p) const {
    return *(envelope.begin()+ Puzzle::getCircularSideId(p+1, envelope.size()));
}

const PointOfEnvelope &Layout::prev(int p) const{
    return *(envelope.begin()+ Puzzle::getCircularSideId(p-1, envelope.size()));
}

void Layout::erase(int p) {
    envelope.erase(envelope.begin()+Puzzle::getCircularSideId(p, envelope.size()));
    //envelopeSides.erase(envelopeSides.begin()+Puzzle::getCircularSideId(p, envelopeSides.size()));
    //calculateAngles();
    //if
}

const PointOfEnvelope &Layout::get(int i) const {
    return envelope[Puzzle::getCircularSideId(i, envelope.size())];
}

const PointOfEnvelope &Layout::getE(int i) const {
    return envelopeEnlarged[Puzzle::getCircularSideId(i, envelopeEnlarged.size())];
}


void Layout::calculateAngles() {
    /*envelope[p].calcAngle(prev(p), next(p));
    prev(p).calcAngle(prev(p-1), get(p));
    next(p).calcAngle(get(p), next(p+1));*/
    sumEnvelope=0;
    angleSumm = 0;
    std::vector<int> toRemove;
    minSide = 1000000000000;
    qualityFactor = 0;
    float envelopeSides_i=0;
    if(envelope.size() > 2){
        for(int i= 0; i<envelope.size(); i++){
            envelope[i].calcAngle(prev(i), next(i));
            envelopeSides_i=envelope[i].distance(next(i));
            if (envelopeSides_i < minSide)
                minSide = envelopeSides_i;
            sumEnvelope += envelopeSides_i;
            angleSumm += envelope[i].getAngle();
            if(envelope[i].getAngle() < 0){
                // !!! i dont like it
                envelope[i].setAngle(2*M_PI+envelope[i].getAngle());
            }
            qualityFactor = qualityFactor + 1/ envelope[i].getAngle();
#ifdef SIMPLIFY
            if(envelopeSides_i < DIM_DELTA) {
                //toRemove.push_back(i);
                envelope.erase(envelope.begin() + i);
                //envelopeSides.erase(envelopeSides.begin() + i);
                return;
                //  toRemove.push_back(CIR(i+1, envelope.size()));
            }
             if (abs(abs(envelope[i].getAngle()) - DEG180) < ANG_DELTA) {

                //toRemove.push_back(i);
                envelope.erase(envelope.begin() + i);
                //envelopeSides.erase(envelopeSides.begin() + i);
                return;
             }

            if (abs(abs(envelope[i].getAngle()) - 2*DEG180) < ANG_DELTA) {

                //toRemove.push_back(i);
                envelope.erase(envelope.begin() + i);
                //envelopeSides.erase(envelopeSides.begin() + i);
                return;
            }

            if (abs(abs(envelope[i].getAngle()) - 0) < ANG_DELTA/2) {

                //toRemove.push_back(i);
                envelope.erase(envelope.begin() + i);
                //envelopeSides.erase(envelopeSides.begin() + i);
                return;
            }
#endif //SIMPLIFY

        }
    }
    /*if(toRemove.size() > 0) {
        for (int i = toRemove.size() - 1; i >= 0; i--) {
            envelope.erase(envelope.begin() + toRemove[i]);
            envelopeSides.erase(envelopeSides.begin() + toRemove[i]);
        }
        for(int i= 0; i<envelope.size(); i++) {
            envelopeSides_i = envelope[i].distance(next(i));
        }
    }*/
}

std::ostream &operator<<(std::ostream &os, const Layout &layout) {
    os << " envelope: " << std::endl;
    for (auto e: layout.envelope){
        os << "    " << e << std::endl;
    };
    return os;
}



 bool Layout::doesPuzzleFit(PuzzleOnBoard * puzzle,
                            int layoutPointId,
                            int layoutNextPointId,
                            int puzzlePointId,
                            int puzzleNextPointId,
                            bool flipped) const{
    float puzzleSideLen=puzzle->getSideLengthS(puzzlePointId, puzzleNextPointId);

    float puzzleAngle=puzzle->getAngle(puzzlePointId);
    float layoutAngle=getAngle(layoutPointId);
    float nextLayoutAngle = getAngle(layoutNextPointId);

    for (int j=0; j < puzzle->pointsCount(); j++){
        float x=puzzle->get(j).getX();
        float y=puzzle->get(j).getY();
        if ((x < (0-DIM_DELTA)) || (x > (BOARDSIZE+DIM_DELTA)) || (y < (0-DIM_DELTA)) || (y > (BOARDSIZE+DIM_DELTA))){
            COUT1("******************* fired F ************************************");
            return false;
        }
        if ( inside(puzzle->get(j)) == 0){
            COUT1("******************* fired E ************************************");
            return false;
        }

    }

//     for (int j=0; j < pointsCount(); j++){
//         if ( puzzle->inside(get(j)) != 0){
//             //COUT("******************* fired D ************************************");
//             return false;
//         }
//
//     }
#ifdef CHECKLINESINTERLACE
    for(int i=0; i < envelope.size(); i++){
        Segment envelopeSegment=Segment(getE(i), getE(i+1));
        for (int j=0; j < puzzle->pointsCount(); j++){
            // don't compare adjacent sides

           Segment puzzleSegment=Segment(puzzle->get(j), puzzle->get(j+1));
            if(envelopeSegment.inters(puzzleSegment)
              )
            {
                COUT1("******************* fired A ************************************");
                return false;

            }
        }
    }
#endif //CHECKLINESINTERLACE
    return true;
}

float Layout::getSideLengthS(int pointId, int nextPointId) const {
//    int pointId_=Puzzle::getCircularSideId(pointId, envelope.size());
//    int nextPointId_=Puzzle::getCircularSideId(nextPointId, envelope.size());
//    if ((pointId_ == pointsCount()-1) && (nextPointId_ ==0))
//        return envelopeSides[pointId_];
//
//    if(pointId_ > nextPointId_)
//        return envelopeSides[nextPointId_];
//    else
//        return envelopeSides[pointId_];


}

float Layout::getAngle(int pointId) const {
    return envelope[pointId].getAngle();
}

float Layout::requiredRotateAngle(const Puzzle &puzzle, int layoutPointId, int layoutNextPointId, int puzzlePointId,
                              int puzzleNextPointId) const {
    return 0;
}

float Layout::getAngleToSegment(int pointId, int nextPointId, const Segment &s) const {
    /*if ((pointId_ == pointsCount()-1) && (nextPointId_ ==0))
        return s.angleBetween(Segment(envelope[pointId_], envelope[nextPointId_]));*/

    int pointId_=Puzzle::getCircularSideId(pointId, envelope.size());
    int nextPointId_=Puzzle::getCircularSideId(nextPointId, envelope.size());
    //if(pointId_ > nextPointId_)
    ///    return s.angleBetween(Segment(envelope[nextPointId_], envelope[pointId_]));
    //else
        return s.angleBetween(Segment(envelope[pointId_], envelope[nextPointId_]));
}

void Layout::modifyEnvelope(PuzzleOnBoard * puzzleOnBoard,
                              int layoutPointId,
                              int layoutNextPointId,
                              int puzzlePointId,
                              int puzzleNextPointId) {
    puzzlesOnBoard.push_back(puzzleOnBoard);
    sumArea += puzzleOnBoard->getArea();
    std::map<int,int> envelopePointsToRemove;
    std::map<int,int> puzzlePointsToRemove;
    envelopePointsToRemove.clear();
    puzzlePointsToRemove.clear();
    //std::unordered_map<int,int> envelopePointsVisited;
    PointOfEnvelope pointOfEnvelope;
    //envelopePointsToVisit.
    /*std::stack<int> envelopePointsToVisit;

    std::stack<int> puzzlePointsToVisit;*/
    //envelopePointsToVisit.push(layoutPointId);
    //puzzlePointsToVisit.push(puzzlePointId);

    //envelopePointsVisited.insert(std::pair<int,int>(puzzlePointId,1));
    envelopePointsToRemove.insert(std::pair<int, int>(layoutPointId,1));
    int curPointOfEnvelope = layoutPointId;
    int curPointOfPuzzle = puzzlePointId;

    std::vector<PointOfEnvelope> removedPoints;

    for(int i=0; i < puzzleOnBoard->pointsCount(); i++) {


        if ((compareAng(puzzleOnBoard->getAngle(curPointOfPuzzle), getAngle(curPointOfEnvelope)) == 0) &&
            (puzzleOnBoard->get(curPointOfPuzzle).distance(envelope[curPointOfEnvelope]) < DIM_DELTA)) {
            envelopePointsToRemove.insert(std::pair<int, int>(curPointOfEnvelope, 1));
            puzzlePointsToRemove.insert(std::pair<int, int>(curPointOfPuzzle, 1));
        }
        curPointOfEnvelope = CIR(curPointOfEnvelope + 1, envelope.size());
        if (!puzzleOnBoard->isIsFlipped()) {
            curPointOfPuzzle = CIR(curPointOfPuzzle + 1, puzzleOnBoard->pointsCount());
        } else {
            curPointOfPuzzle = CIR(curPointOfPuzzle - 1, puzzleOnBoard->pointsCount());
        }
    }


/*        if (compareAng(puzzleOnBoard.getAngle(curPointOfPuzzle), getAngle(curPointOfEnvelope)) == 0) {
            envelopePointsToRemove.insert(std::pair<int, int>(curPointOfEnvelope, 1));
            puzzlePointsToRemove.insert(std::pair<int, int>(curPointOfPuzzle, 1));
            // same length of sides
            if (!puzzleOnBoard.isIsFlipped()) {
                if ((compareDim(getSideLengthS(curPointOfEnvelope, curPointOfEnvelope + 1),
                               puzzleOnBoard.getSideLengthS(curPointOfPuzzle, curPointOfPuzzle + 1)) == 0)
                               && (envelopePointsVisited.find(CIR(curPointOfEnvelope + 1, envelope.size())) ==
                                    envelopePointsVisited.end())
                        ) {
                    envelopePointsToVisit.push(CIR(curPointOfEnvelope + 1, envelope.size()));
                    puzzlePointsToVisit.push(CIR(curPointOfPuzzle + 1, puzzleOnBoard.pointsCount()));
                }

                if ((compareDim(getSideLengthS(curPointOfEnvelope, curPointOfEnvelope - 1),
                               puzzleOnBoard.getSideLengthS(curPointOfPuzzle, curPointOfPuzzle - 1)) == 0)
                               && (envelopePointsVisited.find(CIR(curPointOfEnvelope - 1, envelope.size())) ==
                                             envelopePointsVisited.end())
                        ) {
                    envelopePointsToVisit.push(CIR(curPointOfEnvelope - 1, envelope.size()));
                    puzzlePointsToVisit.push(CIR(curPointOfPuzzle - 1, puzzleOnBoard.pointsCount()));
                }
            }else{
                if ((compareDim(getSideLengthS(curPointOfEnvelope, curPointOfEnvelope + 1),
                               puzzleOnBoard.getSideLengthS(curPointOfPuzzle, curPointOfPuzzle - 1)) == 0)
                                && (envelopePointsVisited.find(CIR(curPointOfEnvelope + 1, envelope.size())) ==
                                    envelopePointsVisited.end())

                        ) {
                    envelopePointsToVisit.push(CIR(curPointOfEnvelope + 1, envelope.size()));
                    puzzlePointsToVisit.push(CIR(curPointOfPuzzle - 1, puzzleOnBoard.pointsCount()));
                }

                if ((compareDim(getSideLengthS(curPointOfEnvelope, curPointOfEnvelope - 1),
                               puzzleOnBoard.getSideLengthS(curPointOfPuzzle, curPointOfPuzzle + 1)) == 0)
                            && (envelopePointsVisited.find(CIR(curPointOfEnvelope - 1, envelope.size())) ==
                                envelopePointsVisited.end())
                    ) {
                        envelopePointsToVisit.push(CIR(curPointOfEnvelope - 1, envelope.size()));
                        puzzlePointsToVisit.push(CIR(curPointOfPuzzle + 1, puzzleOnBoard.pointsCount()));
                    }

                }
            }*/


        int lastBeforeRemoved = CIR((envelopePointsToRemove.begin()->first)-1, envelope.size());
        auto i = envelopePointsToRemove.end();
        while (i != envelopePointsToRemove.begin())
        {
            --i;
            if (i->first <= lastBeforeRemoved)
                lastBeforeRemoved--;
            removedPoints.push_back(get(i->first));
            erase(i->first);
        }

        if(! puzzleOnBoard->isIsFlipped()) {
            int l=puzzlePointId;
            for(int k=0; k< puzzleOnBoard->pointsCount(); k++){
                if (puzzlePointsToRemove.count(l) == 0){

                    //fgIterations++;
                    //std::cout<< fgIterations  << std::endl;

                    pointOfEnvelope = PointOfEnvelope(puzzleOnBoard->get(l).getX(), puzzleOnBoard->get(l).getY());
                    pointOfEnvelope.setAdjacentTuPuzzle(true);
                    if (! insert(++lastBeforeRemoved, pointOfEnvelope)){
                           --lastBeforeRemoved;
                           //delete pointOfEnvelope;
                    }else{
                       // std::cout << " inserted point of envelope " << lastBeforeRemoved << std::endl;
                    }
                }
                l=CIR(l-1, puzzleOnBoard->pointsCount());

            }
            int tmpPointsCount = pointsCount();
            int tmpPointsCountNext = pointsCount()+1;
            while(tmpPointsCount != tmpPointsCountNext){
                tmpPointsCountNext=tmpPointsCount;
                calculateAngles();
                tmpPointsCount=pointsCount();
            }


        }else{ //flipped
            int l=puzzlePointId;
            for(int k=0; k< puzzleOnBoard->pointsCount(); k++){
                if (puzzlePointsToRemove.count(l) == 0){
                    //fgIterations++;
                    //std::cout<< fgIterations  << std::endl;

                    pointOfEnvelope = PointOfEnvelope(puzzleOnBoard->get(l).getX(), puzzleOnBoard->get(l).getY());
                    pointOfEnvelope.setAdjacentTuPuzzle(true);
                    if (! insert(++lastBeforeRemoved,pointOfEnvelope)){
                        --lastBeforeRemoved;
                        //delete pointOfEnvelope;
                    }else{
                        //std::cout << " inserted point of envelope " << lastBeforeRemoved << std::endl;
                    }
                }
                l=CIR(l+1, puzzleOnBoard->pointsCount());

            }
            int tmpPointsCount = pointsCount();
            int tmpPointsCountNext = pointsCount()+1;
            while(tmpPointsCount != tmpPointsCountNext){
                tmpPointsCountNext=tmpPointsCount;
                calculateAngles();
                tmpPointsCount=pointsCount();
            }
        }
        generateEnlarged(MARGIN);
    }




float Layout::getSumArea() const {
    return sumArea;
}

float Layout::getSumEnvelope() const {
    return sumEnvelope;
}

bool Layout::operator==(const Layout &rhs) const {
    return //static_cast<const Polygon &>(*this) == static_cast<const Polygon &>(rhs) &&
           sumArea/10 == rhs.sumArea/10 &&
           sumEnvelope/10 == rhs.sumEnvelope/10 &&
           pointsCount()  == rhs.pointsCount() &&
           puzzleCount() == rhs.puzzleCount();
}


bool Layout::operator!=(const Layout &rhs) const {
    return !(rhs == *this);
}


bool Layout::checkInterlaceWithPuzzles(const std::string & msg){
    for(int i=0;i < pointsCount(); i++){
        for(int j=0; j < puzzlesOnBoard.size(); j++){
            for(int k=0; k < puzzlesOnBoard[j]->pointsCount(); k++){
                //if(Segment(envelope[].))
                if(Segment(envelope[i], envelope[Puzzle::getCircularSideId(i+1, envelope.size())])
                .inters2(Segment(puzzlesOnBoard[j]->get(k), puzzlesOnBoard[j]->get(k+1)))) {
/*                    std::cout << "!!!!!!!!! collision !!!!!!!!!!! " << std::endl;
                    std::cout << "         envelope i, i+1 " << i << " " << i+1 << std::endl;
                    std::cout << "         envelope i, i+1  " << envelope[i] << " "
                                        << envelope[Puzzle::getCircularSideId(i+1, envelope.size())] << std::endl;

                    std::cout << "         puzzle j, j+1 " << k << " " << k+1 << std::endl;
                    std::cout << "         puzzle j, j+1 " << puzzlesOnBoard[j].get(k) << " "
                                          << puzzlesOnBoard[j].get(k+1)<< std::endl;
                    std::cout << "         puzzle id " << puzzlesOnBoard[j].getId() << std::endl;
                    std::cout << "         puzzle rotate angle " << puzzlesOnBoard[j].getRotateAngle() << std::endl;
                    std::cout << "         angle between segments " << Segment(envelope[i], envelope[Puzzle::getCircularSideId(i+1, envelope.size())])
                            .angleBetween(Segment(puzzlesOnBoard[j].get(k), puzzlesOnBoard[j].get(k+1))) << std::endl;
                    std::cout << "         msg " << msg << std::endl;*/
                    //throw std::logic_error("interlace error");
                    return false;
                }
            }
        }
    }
    return true;
}

int Layout::getFgOrigin() const {
    return fgOrigin;
}

void Layout::setFgOrigin(int fgOrigin) {
    Layout::fgOrigin = fgOrigin;
}

float Layout::getMinSide() const {
    return minSide;
}

bool Layout::hasLoop(){
    for(int i=0; i < envelope.size(); i++){
        for(int j=0; j < envelope.size(); j++){
            if((i!=j) && (i!=n(j))){
                if(Segment(envelope[i], envelope[n(i)]).intersStrong(Segment(envelope[j], envelope[n(j)])))
                    return true;
            }
        }
    }
    return false;
}

//const int Layout::inside(const Point &p) const{
//    int wn = 0;
//    for(int i=0; i < pointsCount(); i++){
//        if(get(i).getY() <= p.getY()){
//            if(get(i+1).getY() > p.getY()){
//                if(Segment(get(i), get(i+1)).isLeft(p) > 0){
//                    wn++;
//                }
//            }
//        } else {
//            if(get(i+1).getY() <= p.getY()) {
//                if (get(i + 1).getY() > p.getY()) {
//                    if (Segment(get(i), get(i + 1)).isLeft(p) < 0){
//                        wn--;
//                    }
//                }
//            }
//        }
//    }
//    return wn;
//}


const int Layout::inside(const Point &p) const{
    int wn = 0;
    Segment tmpSeg;
    for(int i=0; i < pointsCount(); i++){
        tmpSeg=Segment(getE(i), getE(i+1));
        if(tmpSeg.pointOnSegment(p))
            return 1;
        if(getE(i).getY() <= p.getY()){
            if(getE(i+1).getY() > p.getY()){
                if(tmpSeg.isLeft(p) > 0){
                    wn++;
                }
            }
        } else {
            if (getE(i + 1).getY() <= p.getY()) {
                if (tmpSeg.isLeft(p) < 0){
                        wn--;
                    }
            }

        }
    }
        return wn;
}

float Layout::getQualityFactor() const {

    float pc = (float) (puzzleCount())/17.0;
    float gamma = 1;
    float alfa = 0.99 * gamma * (1-pc);
    //alfa = 1;
    float beta = 0.01 * gamma * (pc);

    float qf = - (float) (pointsCount())/20.0* alfa +
                        sumArea/104 * beta;
    return qf;

}

const bool Layout::isPromissing(float minAngle, float minSpan) const{
    //float minAngle = 19.0/360.0*(2*M_PI);
    //float minLength = 90;
    float minSumAngle = M_PI;
    int i=0;
//    bool foundAngle=false;
//    bool foundAngle=false;
    for(auto a: envelope){
        //compareAng
        if(compareAng(a.getAngle(), minAngle) < 0){
            //COUT(1 <<  " minAngle " << minAngle);
            return false;
        }
        for(int j=0; j < pointsCount(); j++){
            if ((j != CIR(i+1, pointsCount()) ) &&
                (i != CIR(j+1, pointsCount()) )
                ){
                    float distanceToSeg1 = Segment(get(j+1), get(j+2)).distanceToPoint(get(i));
                    float distanceToSeg2 = Segment(get(j+1), get(j+2)).distanceToPoint(get(i+1));
                    if ((distanceToSeg1 > DIM_DELTA && distanceToSeg1 < minSpan)
                        && (distanceToSeg2 > DIM_DELTA && distanceToSeg2 < minSpan) ) {
//                        COUT(3 << " i,j+1 " << i << "," << CIR(j+1,pointsCount())
//                               << " get(j+1) " << get(j+1)
//                               << " get(j+2) " << get(j+2)
//                               << " get(i) " << get(i)
//                               << " dist1 " << distanceToSeg1
//                               << " dist2 " << distanceToSeg2
//                                  );
                        return false;
                    }
            }
        }
//        if(compareDim(envelopeSides[i++],minSpan) < 0){
//            if (getAngle(i)+getAngle(i+1) < minSumAngle){
////                COUT(2);
//                return false;
//            }
//        }

    }
    return true;

}

void Layout::generateEnlarged(float offset){
    envelopeEnlarged.clear();
    for (int j = 0; j < pointsCount(); j++){
        int i=CIR(j+1, pointsCount());
        int k=CIR(j-1, pointsCount());

        Vector v1 = Vector(envelope[j].getX()-envelope[i].getX(),
                           envelope[j].getY()-envelope[i].getY());
        v1.normalize();
        v1.offset(offset);
        Vector n1 = Vector(-v1.getY(), v1.getX());

        Point pij1 = Point(
                (envelope[i].getX() + n1.getX()),
                (envelope[i].getY() + n1.getY()));
        Point pij2 =  Point(
                (envelope[j].getX() + n1.getX()),
                (envelope[j].getY() + n1.getY()));

        Vector v2 = Vector(
                envelope[k].getX() - envelope[j].getX(),
                envelope[k].getY() - envelope[j].getY());
        v2.normalize();
        v2.offset(offset);
        Vector n2 =  Vector(-v2.getY(), v2.getX());

        Point pjk1 = Point(
                (envelope[j].getX() + n2.getX()),
                (envelope[j].getY() + n2.getY()));
        Point pjk2 = Point(
                (envelope[k].getX() + n2.getX()),
                (envelope[k].getY() + n2.getY()));

        // See where the shifted lines ij and jk intersect.
        //bool lines_intersect, segments_intersect;
        Point poi = (Segment(pij1, pij2).findIntersectionOfLines(Segment(pjk1, pjk2)));
        if(poi.getX() == NAN) {
            poi = PointOfEnvelope(get(j));
        }
        envelopeEnlarged.push_back(PointOfEnvelope(poi));
    }
    for (int j = 0; j < pointsCount(); j++) {
        envelopeEnlarged[j].calcAngle(envelopeEnlarged[CIR(j-1, pointsCount())],
                                           envelopeEnlarged[CIR(j+1, pointsCount())]);
    }



}


/*Layout::Layout(const std::vector<PuzzleOnBoard> &puzzlesOnBoard, const std::vector<PointOfEnvelope> &envelope,
               const std::vector<float> &envelopeSides, const std::stack<int> &envelopePointsToVisit,
               const std::stack<int> &puzzlePointsToVisit) : puzzlesOnBoard(puzzlesOnBoard), envelope(envelope),
                                                             envelopeSides(envelopeSides),
                                                             envelopePointsToVisit(envelopePointsToVisit),
                                                             puzzlePointsToVisit(puzzlePointsToVisit)
                                                             {}*/

/*Layout::Layout(const Layout &o) : puzzlesOnBoard(o.puzzlesOnBoard), envelope(o.envelope),
                                                             envelopeSides(o.envelopeSides),
                                                             envelopePointsToVisit(o.envelopePointsToVisit),
                                                             puzzlePointsToVisit(o.puzzlePointsToVisit)
{}*/

