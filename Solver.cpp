//
// Created by ar on 22.03.2020.
//

#include "Solver.h"
#include "PuzzleOnBoard.h"
#include "PuzzleOnBoardRepo.h"
#include <boost/serialization/priority_queue.hpp>
#include <ctime>
#include <thread>
#include <boost/log/trivial.hpp>
#define DEBUG_FIT (fgIterations < 0)
#define DEBUG (fgIterations < 0) //1288261
#define DEBUG_PROMISSING (fgIterations <= 0)
#define DEBUG_INTERLACE (fgIterations <=  0)
#define SAVE_PRE false
//#define FGITERATIONSSTART 2433636


PuzzleOnBoardRepo puzzleOnBoardRepo;


bool Solver::layNewPuzzle2(Layout &layout, PuzzleList &puzzles, MainWindow *w) {
    PuzzleOnBoard  * puzzleOnBoard = nullptr;
    const Puzzle * puzzle;
    std::string line;
    Layout layoutTmp = layout;
    PuzzleList puzzleListTmp = puzzles;

    float angle;
    short xPoint;
    short yPoint;
    int pointId;
    double vm_usage=0;
    double resident_set=0;

    int refused = 0;
    float envelopeAngleToSegment0 =0;
    float sideAngleToSegment0 = 0;
//    std::string line;
    puzzles.sort();

    auto t_start = std::time(0);
    auto t_end = std::time(0);
    //for (int k : randomVect(puzzles.size())) {
    //for (int k=puzzles.size()-1; k >= 0; --k) {
    for (int k=0; k < puzzles.size(); ++k) {
        puzzle = puzzles.get(k);
        Fit fitResult;
        int nextJ = 0;
        bool flipped = false;
        for (int i : randomVect(layout.pointsCount())) {
            if (layout.isAdjacentToPuzzle(i)){

                for (int j : randomVect(puzzle->getSidesIterable())) {
                    /*if(abs(abs(puzzle.getAngle(j))-abs(layout.getAngle(i)))ff > ANG_DELTA )
                        continue;*/
                    for(int x=0; x < (puzzle->isTwoSided()?2:1); x++){


                        if(x==0){
                            nextJ=j+1;
                            flipped=false;
                        }else{
                            nextJ=j-1;
                            flipped=true;
                        }
                        sideAngleToSegment0 =  puzzle->getAngleToSegment(j,nextJ,SEGMENT0,flipped);
                        envelopeAngleToSegment0 = layout.getAngleToSegment(i, i + 1,SEGMENT0);


                        if(flipped) {
                            angle=sideAngleToSegment0 + envelopeAngleToSegment0;
                            //puzzleOnBoard->rotate(sideAngleToSegment0 + envelopeAngleToSegment0, j)
                            //        .translate(layout.get(i));
                        }
                        else{
                            angle=envelopeAngleToSegment0 - sideAngleToSegment0;
//                            puzzleOnBoard->rotate( envelopeAngleToSegment0 - sideAngleToSegment0, j)
//                                    .translate(layout.get(i));
                        }

                        xPoint = layout.get(i).getX();
                        yPoint = layout.get(i).getY();
                        pointId = j;

                        puzzleOnBoard = puzzleOnBoardRepo.get(puzzle->getId(),
                                                                xPoint,
                                                                yPoint,
                                                                pointId,
                                                                flipped);
                        bool wasInRepo;
                        if(puzzleOnBoard == nullptr){

                            puzzleOnBoard = new PuzzleOnBoard(puzzle,
                                                              Point(0, 0),
                                                              0, true, 0);
                            puzzleOnBoard->reset();
                            if(flipped){
                                puzzleOnBoard->flip();
                            }
                            puzzleOnBoard->rotate(angle, pointId);
                            puzzleOnBoard->translate(layout.get(i));


                            wasInRepo = false;
                        }else{
                            wasInRepo = true;
                            puzzleOnBoard->setInRepository();
                        }
                        //puzzleOnBoard->printPuzzle();
                        fcIterations++;
                        if (layout.doesPuzzleFit(puzzleOnBoard, i, i + 1, j, nextJ, flipped)) {
                            if ( ! wasInRepo && ! puzzleOnBoard->isInRepository()){
                                puzzleOnBoardRepo.set(puzzleOnBoard->hash_value(), puzzleOnBoard);
                            }
                            fgIterations++;
                            if(fgIterations%10000 == 0){
                                process_mem_usage(vm_usage, resident_set);
                                t_end = std::time(0);
                                COUT ("fg " << fgIterations
                                              << " fc " << fcIterations
                                                      << " stackSize " << stackSize
                                                      << " casheSize " << layoutSet.size()
                                                      << " hit/miss+hit " << (float)cache_hits/((float)cache_misses+(float)cache_hits)
                                                      << " maxArea " << maxArea
                                                      << " repoSize " << puzzleOnBoardRepo.getSize()
                                                      << " hit/miss+hit " << ((float)puzzleOnBoardRepo.hit/( (float)puzzleOnBoardRepo.hit +  (float)puzzleOnBoardRepo.miss))
                                                      << " timestamp " << t_end
                                                      << " mem "<< vm_usage << " " <<resident_set);
                                //printBuckets();
                                //prevClock=std::clock();

                            }


                            if (DEBUG) {
                                if(w != nullptr) w->setLayout(&layout);
                                if(w != nullptr) w->pPaintPuzzle();
                                std::getline(std::cin, line);

                            }

                            BOOST_LOG_TRIVIAL(trace) << fgIterations << " "<<layout.getFgOrigin() ;

                            layout.modifyEnvelope(puzzleOnBoard,
                                                  i, i+1,
                                                  j, nextJ);
                            layout.setFgOrigin(fgIterations);
//                            if(!  layout.isPromissing(puzzles.getMinAngle(),puzzles.getMinSpan())) {
////                                //error, skip current loop
//                                if(DEBUG_PROMISSING){
//                                    w->setLayout(&layout);
//                                    w->pPaintPuzzle();
//                                    std::getline(std::cin, line);
//                                }
//                                //COUT("********** NOT PROMISSING **********");
//                                layout = layoutTmp;
//                                puzzles = puzzleListTmp;
//                                continue;
//                            }
                            if(DEBUG_INTERLACE){

                                if(! layout.checkInterlaceWithPuzzles(std::to_string(fgIterations))){
                                    QString filename =
                                            QString::number(layout.getSumArea())
                                            +QString("_previnterlace_")
                                            +QString::number(layout.getFgOrigin())+QString(".png");

                                    if(w != nullptr) paintLayout(layoutTmp, filename, w);

                                    filename = QString::number(layout.getSumArea())+QString("_interlace_")+
                                               QString::number(fgIterations)+QString(".png");

                                    if(w != nullptr) paintLayout(layout, filename, w);
                                    std::getline(std::cin, line);
                                };

                            }
                            puzzles.erase(k);
                            if (DEBUG) {
                                if(w != nullptr) w->setLayout(&layout);
                                if(w != nullptr) w->pPaintPuzzle();
                                std::getline(std::cin, line);

                            }
                            if ( (SAVELOG > 0) || (stackSize > solverConfig.QUEUE_SIZE) ) {
                                if(fgIterations%SAVELOG == 0 || stackSize > solverConfig.QUEUE_SIZE){
                                    if (solverConfig.SAVE_AFTER_LIMIT){
                                        std::ofstream ofsl((QString::number(fgIterations)+QString("savelog_layout")).toStdString());

                                        boost::archive::text_oarchive oal(ofsl);
                                        // write class instance to archive
                                        oal << puzzles;
                                        oal << layout;

                                        oal << stackSize;
                                        oal << layoutSet;
                                        oal << fgIterations;
                                        ofsl.close();
                                    }
                                    if(stackSize > solverConfig.QUEUE_SIZE)
                                        exit(0);

                                }
                            }
                            if(layout.getSumArea() > maxArea || puzzles.size() < 1) {
                                if(layout.getSumArea() > maxArea)
                                    maxArea = layout.getSumArea();
                                QString filename;
                                if(SAVE_PRE){
                                    filename =
                                            QString::number(layout.getSumArea())
                                            +QString("_prevmaxarea_")
                                            +QString::number(layout.getFgOrigin())+QString(".png");

                                    if(w != nullptr) paintLayout(layoutTmp, filename, w);
                                }
                                filename = QString::number(layout.getSumArea())+QString("_maxarea_")+
                                           QString::number(fgIterations)+QString(".png");

                                if(w != nullptr) paintLayout(layout, filename, w);




                            }
                            if(solverConfig.CLEAR_LAYOUT_PUZZLE_LIST)
                                layout.clearPuzzleList();

                            push_back_to_stack(std::make_pair(layout, puzzles));
                            if(puzzles.size() == 0)
                                return true;
                            layout = layoutTmp;
                            puzzles = puzzleListTmp;
                            puzzleOnBoard = nullptr;
                        }else{ // does not fit

                            if(DEBUG_FIT){
                                COUT("does not fit");
                                layout.modifyEnvelope(puzzleOnBoard,
                                                      i, i+1,
                                                      j, nextJ);
                                if(w != nullptr) w->setLayout(&layout);
                                if(w != nullptr) w->pPaintPuzzle();
                                std::getline(std::cin, line);

                                //layout = layoutTmp;
                                //puzzles = puzzleListTmp;

                            }
                            if(! puzzleOnBoard->isInRepository() ){
                                // does not fit and is not in repository
                                delete puzzleOnBoard;
                            }
                            puzzleOnBoard = nullptr;
                        }
                    }
                }
            }
        }
        //std::cout << "refused " << refused << std::endl;
        //elete puzzleOnBoard;
    }



    return false;
}



void Solver::solvePuzzles( MainWindow * w, QString layoutFilename, int iStart, int iSize){
    std::string line;
    int minPuzzle = 100;
    fgIterations = 0;
    fcIterations=0;
    //while( ! finish) {
    Layout layoutFromStack;
    PuzzleList  puzzleListFromStack;
    Layout layout;
    PuzzleList puzzles;
    int prevIterations=0;
    std::vector<PuzzleOnBoard> unusedPuzzleList;
    int minPuzzles=100;

    Layout prevLayout;
    if(w != nullptr) w->setLayout(&layout);



    if(! (layoutFilename.trimmed().isEmpty())) {
//        std::ifstream ifsl(layoutFilename.toStdString());
//        boost::archive::text_iarchive ial(ifsl);
//        // read class state from archive
//        ial >> puzzles;
//        ial >> layout;
//        //ial >> layoutStack;
//        ial >> layoutSet;
//        ial >> fgIterations;
//        maxArea = layout.getSumArea();
//        ifsl.close();
//        if(iStart != -1){
//            int i=0;
//            while(i++<iStart && !layoutStack.empty()){
//                layoutStack.pop();
//            }
//        }
//        if(iSize != -1) {
//            int i=0;
//            std::priority_queue<std::pair<Layout, PuzzleList>, std::vector<std::pair<Layout, PuzzleList>>, CompareLayoutsClass> layoutStackTmp;
//            while (i++<iSize && !layoutStack.empty() ){
//                layoutStackTmp.push(layoutStack.top());
//                layoutStack.pop();
//            }
//            layoutStack=layoutStackTmp;
//        }
//        COUT(layoutStack.size())
    }else {

        PointOfEnvelope pointOfEnvelope;
        pointOfEnvelope = PointOfEnvelope(0, 0);
        pointOfEnvelope.setAdjacentTuPuzzle(true);
        layout.push_back(pointOfEnvelope);
        pointOfEnvelope = PointOfEnvelope(BOARDSIZE, 0);
        layout.push_back(pointOfEnvelope);
        pointOfEnvelope = PointOfEnvelope(BOARDSIZE, BOARDSIZE);
        layout.push_back(pointOfEnvelope);
        pointOfEnvelope = PointOfEnvelope(0, BOARDSIZE);
        layout.push_back(pointOfEnvelope);
        layout.generateEnlarged(MARGIN);

        puzzles.generateSimplified();

        if(solverConfig.INITIAL_LAYOUT_NOT_EMPTY){
            PuzzleOnBoard * pob = new PuzzleOnBoard(puzzles.get(0), Point(0, 0), 0, false, 0);
            pob->translate(Point(0, 0));
            layout.modifyEnvelope(pob, 0, 1, 0, 1);
            pob = new PuzzleOnBoard(puzzles.get(1), Point(0, 0), 0, false, 0);
            pob->translate(Point(520, 0));
            layout.modifyEnvelope(pob, 5, 0, 0,
                                  1);
            pob = new PuzzleOnBoard(puzzles.get(2), Point(0, 0), 0, false, 0);
            pob->rotate(DEG180 / 4, 0);
            pob->translate(Point(515, 0));
            layout.modifyEnvelope(pob,
                    5, 6, 0, 1);
            puzzles.erase(0);
            puzzles.erase(0);
            puzzles.erase(0);
        }
        layout.setAdjacentToPuzzle(0, true);
        puzzles.sort();
        push_back_to_stack(std::make_pair(layout, puzzles));
    }


    float totalarea=0;
    for (auto p = puzzles.cbegin(); p!=puzzles.cend(); p++)
        totalarea = totalarea + (*p)->getArea();

    COUT("total sumArea " << totalarea);

    while (stackSize > 0 ) {
    //while(true){
        std::pair<Layout, PuzzleList> fromStack=top_stack();
        layoutFromStack=fromStack.first;
        puzzleListFromStack=fromStack.second;
//        if (puzzleListFromStack.size() > 0) {
//            if ((prevLayout.pointsCount() == 0 ) || (prevLayout != layoutFromStack))
            layNewPuzzle2(layoutFromStack, puzzleListFromStack, w);
//            prevLayout=layoutFromStack;



//            if ((puzzleListFromStack.size() <= 0)){
//                if(w != nullptr) w->setLayout(&layoutFromStack);
//                unusedPuzzleList.clear();
//                int n=0;
//                for(int i=0; i < puzzleListFromStack.size(); i++){
//                    unusedPuzzleList.push_back(PuzzleOnBoard(puzzleListFromStack.get(i), Point(0,0), 0, false, 0)
//                                                       .translate(Point(0,300*n++)));
//                }
//                if(w != nullptr) w->setPuzzlesOnBoard(unusedPuzzleList);
//
//                if(w != nullptr) w->pPaintPuzzle();
//                std::this_thread::sleep_for(std::chrono::milliseconds(100));
//                QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
//                                   QString::number(fgIterations)+QString(".png");
//                if(w != nullptr) w->grab().save(filename);
//                std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            }
//
//        }else{
//            if(w != nullptr) w->setLayout(&layoutFromStack);
//            unusedPuzzleList.clear();
//            int n=0;
//            for(int i=0; i < puzzleListFromStack.size(); i++){
//                unusedPuzzleList.push_back(PuzzleOnBoard(puzzleListFromStack.get(i), Point(0,0), 0, false, 0)
//                                                   .translate(Point(0,300*n++)));
//            }
//            if(w != nullptr) w->setPuzzlesOnBoard(unusedPuzzleList);
//
//            if(w != nullptr) w->pPaintPuzzle();
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//            QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
//                               QString::number(fgIterations)+QString(".png");
//            if(w != nullptr) w->grab().save(filename);
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
//
//
        //}

    }
    COUT("EEEEEEEEEEEEEEEEENNNNNNNNNNNNNNNNNNNNDDDDDDDDDDDDDDDDDDDDDDD");
    if(w != nullptr) w->setLayout(&layoutFromStack);
    if(w != nullptr) w->pPaintPuzzle();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
                       QString::number(fgIterations)+QString(".png");
    if(w != nullptr) w->grab().save(filename);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

/*    std::ofstream ofsl(QString("layoutSet").toStdString());

    boost::archive::text_oarchive oal(ofsl);
    // write class instance to archive
    oal << layoutSet;

    ofsl.close();*/


    //prevIterations=iterations;
    exit(0);
}

void Solver::setSolverConfig(const SolverConfig &solverConfig) {
    Solver::solverConfig = solverConfig;
}

void  Solver::push_back_to_stack(std::pair<Layout, PuzzleList> p) {
    //if(layoutSet.count(LayoutCacheImage(p.first, p.second)) == 0){
    //    layoutSet.insert({LayoutCacheImage(p.first,  p.second),1});
        layoutStackBuckets[p.first.getBucket()].push(p);
        //layoutStack.push(p);
        stackSize++;
//        cache_misses++;
//    } else{
//        cache_hits++;
//    }

}

std::pair<Layout, PuzzleList>  Solver::top_stack()
{
    for(int i=1; i < MAX_BUCKETS; i ++){
        if(layoutStackBuckets.count(i)>0){
            if(! layoutStackBuckets[i].empty()){
                std::pair<Layout, PuzzleList> ret = layoutStackBuckets[i].top();
                layoutStackBuckets[i].pop();
                stackSize--;
                return ret;
            }
        }
    }
};

void Solver::printBuckets(){
    COUT("  buckets: ");
    for(int i=1; i < MAX_BUCKETS; i ++) {
        if(layoutStackBuckets.count(i)>0) {
            COUT("        " << i<< " " <<  layoutStackBuckets[i].size());
        }
    }
};

