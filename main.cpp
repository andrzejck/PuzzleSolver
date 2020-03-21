//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define MAIN
#define BOOST_TEST_MODULE My Test

#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "point.h"
#include "Segment.h"
#include "puzzle.h"
#include "PuzzleList.h"
#include "PuzzleOnBoard.h"
#include "Layout.h"
#include <thread>
#include <chrono>
#include <algorithm>
#include <random>
#include <stack>
#include <queue>
#include <unordered_map>
#include "LayoutCacheImage.h"
#include <chrono>
#include <set>


#include <boost/test/unit_test.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/serialization/priority_queue.hpp>





PuzzleList pl;
#define SHOW_WINDOW 1
#define REPORT_TRESHOLD 13
#define LAYOUT_POINT_TRESHOLD 5000
#define QUEUE_SIZE 100000
#define SAVE_AFTER_LIMIT false
#define COUT(x) std::cout << x << std::endl;
#define DEBUG_FIT (fgIterations < 0)
#define DEBUG (fgIterations < 0)
#define DEBUG_PROMISSING (fgIterations <= 0)
#define DEBUG_INTERLACE (fgIterations <=  0)
#define SAVE_PRE false
//#define FGITERATIONSSTART 2433636
//#define READ_FROM_FILE "700000savelog_layout"
#define SAVELOG 20000000


float maxArea =0;

std::clock_t prevClock;
#define LAMBDA -1
#define FITSCALE 1
//std::random_device rd;
//std::mt19937 g(rd());
std::set<int> skipIt;


QString layoutFilename;



bool CompareLayouts (const std::pair<Layout,PuzzleList> & l1, const std::pair<Layout,PuzzleList> & l2) {
//    if(l1.first.getQualityFactor() == l2.first.getQualityFactor()) {
//        return l1.first.pointsCount() < l2.first.pointsCount();
//    }else {
//        return (float) (l1.first.getQualityFactor())  >
//               (float) (l2.first.getQualityFactor()) ;
//    }
//    return l1.first.pointsCount() < l2.first.pointsCount();

    if(l1.first.pointsCount() == l2.first.pointsCount()) {
        //return l1.first.getSumArea() > l2.first.getSumArea();
        return l1.first.getQualityFactor() > l2.first.getQualityFactor();
    }else {
        return l1.first.pointsCount() < l2.first.pointsCount() ;
    }

}

struct CompareLayoutsClass{
    bool operator() (std::pair<Layout,PuzzleList> & l1, std::pair<Layout,PuzzleList> & l2){
        return CompareLayouts(l2,l1);
    }
};


//std::stack<std::pair<Layout, PuzzleList>> layoutStack;
//std::vector<std::pair<Layout, PuzzleList>> layoutStack;
std::priority_queue<std::pair<Layout, PuzzleList>, std::vector<std::pair<Layout, PuzzleList>>, CompareLayoutsClass> layoutStack;
std::unordered_map<LayoutCacheImage, int, LayoutCacheImageHashFunction> layoutSet;

//void push_back_to_stack(std::pair<Layout, PuzzleList> p) {
//    if(layoutSet.count(p.first) == 0){
//        layoutStack.push(p);
//        layoutSet.insert({p.first,1});
//    }
//}
//
//std::pair<Layout, PuzzleList> top_stack()
//{
//    std::pair<Layout, PuzzleList> ret=layoutStack.top();
//    //layoutSet.erase(ret.first);
//    layoutStack.pop();
////    COUT(ret.first.pointsCount());
//    return ret;
//};

void push_back_to_stack(std::pair<Layout, PuzzleList> p) {
    if(layoutSet.count(LayoutCacheImage(p.first, p.second)) == 0){
        layoutSet.insert({LayoutCacheImage(p.first,  p.second),1});
        layoutStack.push(p);
    }
}

std::pair<Layout, PuzzleList> top_stack()
{
    /*float r=((float) rand() / (RAND_MAX));
    int index=0;
    if (LAMBDA > 0)
        index=-(1/LAMBDA)*log(r);
    if (index >= layoutStack.size())
        index = 0;
    std::pair<Layout, PuzzleList> ret=*(layoutStack.begin()+index);
    //layoutSet.erase(ret.first);
    layoutStack.erase(layoutStack.begin()+index);
    return ret;*/
    std::pair<Layout, PuzzleList> ret=layoutStack.top();
    layoutStack.pop();
    return ret;

};

void shuffleStack(){
    //std::sort(layoutStack.begin(), layoutStack.end(), CompareLayouts);
    //if(layoutStack.size()  > QUEUE_SIZE)
    //    layoutStack.resize(QUEUE_SIZE);
}



auto rng = std::default_random_engine {};
bool finish = false;

long iterations=0;
long fgIterations=0;



std::vector<int> randomVect(int r){
    std::vector<int> res(r);
    std::iota (std::begin(res), std::end(res), 0);
    //std::random_shuffle(std::begin(res), std::end(res));
    return res;
}

void paintLayout(Layout & layout, QString filename, MainWindow * w){
    w->setLayout(&layout);
    w->pPaintPuzzle();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    w->grab().save(filename);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}



bool layNewPuzzle2(Layout &layout, PuzzleList &puzzles, MainWindow *w) {
    PuzzleOnBoard  * puzzleOnBoard;
    Puzzle puzzle("");
    std::string line;
    Layout layoutTmp = layout;
    PuzzleList puzzleListTmp = puzzles;
    int combinations = 0;

    int refused = 0;
    float envelopeAngleToSegment0 =0;
    float sideAngleToSegment0 = 0;
//    std::string line;
    puzzles.sort();
    prevClock=std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    //for (int k : randomVect(puzzles.size())) {
    //for (int k=puzzles.size()-1; k >= 0; --k) {
    for (int k=0; k < puzzles.size(); ++k) {

        puzzle = puzzles.get(k);
        puzzleOnBoard = new PuzzleOnBoard(puzzle,
                                          Point(0, 0),
                                          0, true, 0);
        puzzleOnBoard->setColor(Qt::black);
        Fit fitResult;
        int nextJ = 0;
        bool flipped = false;
        for (int i : randomVect(layout.pointsCount())) {
            if (layout.isAdjacentToPuzzle(i)){
                for (int j : randomVect(puzzle.getSidesIterable())) {
                    /*if(abs(abs(puzzle.getAngle(j))-abs(layout.getAngle(i)))ff > ANG_DELTA )
                        continue;*/
                    for(int x=0; x < (puzzle.isTwoSided()?2:1); x++){

                        if(x==0){
                            nextJ=j+1;
                            flipped=false;
                        }else{
                            nextJ=j-1;
                            flipped=true;
                        }
                        puzzleOnBoard->reset();
                        if(flipped){
                            puzzleOnBoard->flip();
                        }
                        sideAngleToSegment0 =  puzzleOnBoard->getAngleToSegment(j,nextJ,SEGMENT0);
                        envelopeAngleToSegment0 = layout.getAngleToSegment(i, i + 1,SEGMENT0);

                        if(flipped) {
                            puzzleOnBoard->rotate(sideAngleToSegment0 + envelopeAngleToSegment0, j)
                                    .translate(layout.get(i));
                        }
                        else{
                            puzzleOnBoard->rotate( envelopeAngleToSegment0 - sideAngleToSegment0, j)
                                    .translate(layout.get(i));
                        }
                        if (layout.doesPuzzleFit(*puzzleOnBoard, i, i + 1, j, nextJ, flipped)) {

                            fgIterations++;
                            if(fgIterations%1000 == 0){
                                auto t_end = std::chrono::high_resolution_clock::now();

                                COUT ("fgIterations " << fgIterations
                                                                                    << " stackSize " << layoutStack.size()
                                                                                    << " casheSize " << layoutSet.size()
                                                                                    << " speed " << 1000/( std::chrono::duration<float, std::milli>(t_end-t_start).count())
                                                                                    << " maxArea " << maxArea);
                                prevClock=std::clock();
                                t_start = std::chrono::high_resolution_clock::now();



                            }
                            if (DEBUG) COUT("    fgIterations " << fgIterations);

                            if (DEBUG) {
                                w->setLayout(&layout);
                                w->pPaintPuzzle();
                                std::getline(std::cin, line);

                            }
                            if(skipIt.count(fgIterations) > 0)
                                continue;
                            BOOST_LOG_TRIVIAL(trace) << fgIterations << " "<<layout.getFgOrigin() ;

                            layout.modifyEnvelope(*puzzleOnBoard,
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

                                    paintLayout(layoutTmp, filename, w);

                                    filename = QString::number(layout.getSumArea())+QString("_interlace_")+
                                                       QString::number(fgIterations)+QString(".png");

                                    paintLayout(layout, filename, w);
                                    std::getline(std::cin, line);
                                };

                            }
                            puzzles.erase(k);
                            if (DEBUG) {
                                w->setLayout(&layout);
                                w->pPaintPuzzle();
                                std::getline(std::cin, line);

                            }
                            if ( (SAVELOG > 0) || (layoutStack.size() > QUEUE_SIZE) ) {
                                if(fgIterations%SAVELOG == 0 || layoutStack.size() > QUEUE_SIZE){
                                    if (SAVE_AFTER_LIMIT){
                                        std::ofstream ofsl((QString::number(fgIterations)+QString("savelog_layout")).toStdString());

                                        boost::archive::text_oarchive oal(ofsl);
                                        // write class instance to archive
                                        oal << puzzles;
                                        oal << layout;

                                        oal << layoutStack;
                                        oal << layoutSet;
                                        oal << fgIterations;
                                        ofsl.close();
                                    }
                                    if(layoutStack.size() > QUEUE_SIZE)
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

                                    paintLayout(layoutTmp, filename, w);
                                }
                                filename = QString::number(layout.getSumArea())+QString("_maxarea_")+
                                                   QString::number(fgIterations)+QString(".png");

                                paintLayout(layout, filename, w);




                            }

                            push_back_to_stack(std::make_pair(layout, puzzles));
                            if(puzzles.size() == 0)
                                return true;
                            layout = layoutTmp;
                            puzzles = puzzleListTmp;
                        }else{ // does not fit
                            if(DEBUG_FIT){
                                COUT("does not fit");
                                layout.modifyEnvelope(*puzzleOnBoard,
                                                      i, i+1,
                                                      j, nextJ);
                                w->setLayout(&layout);
                                w->pPaintPuzzle();
                                std::getline(std::cin, line);

                                layout = layoutTmp;
                                puzzles = puzzleListTmp;

                            }
                        }
                    }
                }
            }
        }
        //std::cout << "refused " << refused << std::endl;
        delete puzzleOnBoard;
    }



    return false;
}



void solvePuzzles( MainWindow * w, QString layoutFilename, int iStart=-1, int iSize = -1 ){
    std::string line;
    int minPuzzle = 100;

    //while( ! finish) {
    Layout layoutFromStack;
    PuzzleList  puzzleListFromStack;
    Layout layout;
    PuzzleList puzzles;
    int prevIterations=0;
    std::vector<PuzzleOnBoard> unusedPuzzleList;
    int minPuzzles=100;
    int prevStack=layoutStack.size();
    Layout prevLayout;
    w->setLayout(&layout);



    if(! (layoutFilename.trimmed().isEmpty())) {
        std::ifstream ifsl(layoutFilename.toStdString());
        boost::archive::text_iarchive ial(ifsl);
        // read class state from archive
        ial >> puzzles;
        ial >> layout;
        ial >> layoutStack;
        ial >> layoutSet;
        ial >> fgIterations;
        maxArea = layout.getSumArea();
        ifsl.close();
        if(iStart != -1){
            int i=0;
            while(i++<iStart && !layoutStack.empty()){
                layoutStack.pop();
            }
        }
        if(iSize != -1) {
            int i=0;
            std::priority_queue<std::pair<Layout, PuzzleList>, std::vector<std::pair<Layout, PuzzleList>>, CompareLayoutsClass> layoutStackTmp;
            while (i++<iSize && !layoutStack.empty() ){
                layoutStackTmp.push(layoutStack.top());
                layoutStack.pop();
            }
            layoutStack=layoutStackTmp;
        }
        COUT(layoutStack.size())
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


//        PuzzleOnBoard pob = PuzzleOnBoard(puzzles.get(0), Point(0, 0), 0, false, 0).translate(Point(0, 0));
//        layout.modifyEnvelope(pob, 0, 1, 0, 1);
//        layout.modifyEnvelope(PuzzleOnBoard(puzzles.get(1), Point(0, 0), 0, false, 0).translate(Point(520, 0)), 5, 0, 0,
//                              1);
//        layout.modifyEnvelope(
//                PuzzleOnBoard(puzzles.get(2), Point(0, 0), 0, false, 0).rotate(DEG180 / 4, 0).translate(Point(515, 0)),
//                5, 6, 0, 1);
//        puzzles.erase(0);
//        puzzles.erase(0);
//        puzzles.erase(0);

        layout.setAdjacentToPuzzle(0, true);
        puzzles.sort();
        push_back_to_stack(std::make_pair(layout, puzzles));
    }


    float totalarea=0;
    for (auto p = puzzles.cbegin(); p!=puzzles.cend(); p++)
        totalarea = totalarea + p->getArea();

    COUT("total sumArea " << totalarea);

    while (! layoutStack.empty() ) {
        shuffleStack();
        std::pair<Layout, PuzzleList> fromStack=top_stack();
        layoutFromStack=fromStack.first;
        puzzleListFromStack=fromStack.second;
        if (puzzleListFromStack.size() > 0) {
            if ((prevLayout.pointsCount() == 0 ) || (prevLayout != layoutFromStack))
                layNewPuzzle2(layoutFromStack, puzzleListFromStack, w);
            prevLayout=layoutFromStack;



            if ((puzzleListFromStack.size() <= 0)){
                w->setLayout(&layoutFromStack);
                unusedPuzzleList.clear();
                int n=0;
                for(int i=0; i < puzzleListFromStack.size(); i++){
                    unusedPuzzleList.push_back(PuzzleOnBoard(puzzleListFromStack.get(i), Point(0,0), 0, false, 0)
                                                       .translate(Point(0,300*n++)));
                }
                w->setPuzzlesOnBoard(unusedPuzzleList);

                w->pPaintPuzzle();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
                                   QString::number(iterations)+QString(".png");
                w->grab().save(filename);
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                prevIterations=iterations;


            }




            iterations++;

        }else{
            w->setLayout(&layoutFromStack);
            unusedPuzzleList.clear();
            int n=0;
            for(int i=0; i < puzzleListFromStack.size(); i++){
                unusedPuzzleList.push_back(PuzzleOnBoard(puzzleListFromStack.get(i), Point(0,0), 0, false, 0)
                                                   .translate(Point(0,300*n++)));
            }
            w->setPuzzlesOnBoard(unusedPuzzleList);

            w->pPaintPuzzle();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
                               QString::number(iterations)+QString(".png");
            w->grab().save(filename);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            prevIterations=iterations;

        }

    }
    COUT("EEEEEEEEEEEEEEEEENNNNNNNNNNNNNNNNNNNNDDDDDDDDDDDDDDDDDDDDDDD");
    w->setLayout(&layoutFromStack);
    w->pPaintPuzzle();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    QString filename = QString::number(puzzleListFromStack.size())+QString("_")+
                       QString::number(iterations)+QString(".png");
    w->grab().save(filename);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

/*    std::ofstream ofsl(QString("layoutSet").toStdString());

    boost::archive::text_oarchive oal(ofsl);
    // write class instance to archive
    oal << layoutSet;

    ofsl.close();*/


    prevIterations=iterations;
    exit(0);
}



BOOST_AUTO_TEST_CASE( my_test )
{
    Layout layout;



    PuzzleList pl;
    PuzzleList pl1;
    BOOST_CHECK( pl == pl1);
    pl.generateSimplified();
    BOOST_CHECK( layout.pointsCount() == 0);
    BOOST_CHECK( pl.get(0) == pl.get(1));
    BOOST_CHECK( pl.get(1) != pl.get(2));
    BOOST_CHECK( pl != pl1);
    pl1 = pl;
    BOOST_CHECK( pl == pl1);
    pl.erase(0);
    BOOST_CHECK( pl != pl1);
    pl1.erase(1);
    BOOST_CHECK( pl == pl1);

    std::ofstream ofs("PuzzleList");

    boost::archive::text_oarchive oa(ofs);
    // write class instance to archive
    oa << pl;
    ofs.close();
    PuzzleList pl2;

    std::ifstream ifs("PuzzleList");
    boost::archive::text_iarchive ia(ifs);
    // read class state from archive
    ia >> pl2;
    BOOST_CHECK( pl == pl2);
    ifs.close();

    pl.generateSimplified();

    Layout layout1;
    BOOST_CHECK( layout == layout1);

    PointOfEnvelope pointOfEnvelope;
    pointOfEnvelope = PointOfEnvelope(100,100);
    pointOfEnvelope.setAdjacentTuPuzzle(true);
    layout.push_back(pointOfEnvelope);
    pointOfEnvelope = PointOfEnvelope(200,200);
    layout.push_back(pointOfEnvelope);
    pointOfEnvelope = PointOfEnvelope(200,100);
    layout.push_back(pointOfEnvelope);
    pointOfEnvelope = PointOfEnvelope(100,200);
    layout.push_back(pointOfEnvelope);
    COUT(layout.inside(Point(100,100)) );
    COUT(layout.inside(Point(10,10)) );
    COUT(layout.inside(Point(120,150)) );
    COUT(layout.inside(Point(170,150)) );
    COUT(layout.inside(Point(150,170)) );
    COUT(layout.inside(Point(150,150)) );
    COUT(layout.inside(Point(200,200)) );
    COUT(layout.inside(Point(110,110)) );
    COUT(layout.inside(Point(1000,1000)) );
    BOOST_CHECK( layout.inside(Point(150,150)) != 0);
    BOOST_CHECK( layout.inside(Point(10,10)) == 0);
    BOOST_CHECK( layout.inside(Point(1000,1000)) == 0);
    BOOST_CHECK( layout.inside(Point(-1000,-1000)) == 0);
    BOOST_CHECK( layout.inside(Point(1000,-1000)) == 0);
    /*PuzzleList puzzles;
    puzzles.generateSimplified();

    layout.modifyEnvelope(PuzzleOnBoard(puzzles.get(0), Point(0,0), 0,false,0).translate(Point(0,0)), 0,1,0,1);
    layout.modifyEnvelope(PuzzleOnBoard(puzzles.get(1), Point(0,0), 0,false,0).translate(Point(530,0)), 5,0,0,1);
    layout.modifyEnvelope(PuzzleOnBoard(puzzles.get(2), Point(0,0), 0,false,0).rotate(DEG180/4, 0).translate(Point(520,5)), 5,6,0,1);
    layout.setAdjacentToPuzzle(0, true);

    puzzles.erase(0);
    puzzles.erase(0);
    puzzles.erase(0);
    puzzles.sort();

    BOOST_CHECK( layout != layout1);

    std::ofstream ofsl("layout");

    boost::archive::text_oarchive oal(ofsl);
    // write class instance to archive
    oal << layout;
    ofsl.close();


    std::ifstream ifsl("layout");
    boost::archive::text_iarchive ial(ifsl);
    // read class state from archive
    ial >> layout1;
    BOOST_CHECK( layout == layout1);
    ifsl.close();*/
}
namespace logging = boost::log;

#ifdef MAIN
int main(int argc, char *argv[])
{
    logging::add_file_log("layout.log");

//    skipIt.insert(894119);
//    skipIt.insert(894140);
//    skipIt.insert(894141);
//    skipIt.insert(1069158);
////    894687
////    1069159
//    skipIt.insert(1084816);
    int iStart=-1;
    int iSize=-1;
    if(argc > 1)
        layoutFilename = QString(argv[1]);
    if(argc > 2)
        iStart = QString(argv[2]).toInt();
    if(argc > 3)
        iSize = QString(argv[3]).toInt();


    std::srand(unsigned(time(0)));
#ifdef SHOW_WINDOW
    QApplication a(argc, argv);
    MainWindow w;
#endif

#ifdef SHOW_WINDOW
    std::thread th1(solvePuzzles,  &w, layoutFilename, iStart, iSize);
    //w.setFixedWidth(1000);
    w.setFixedSize(1000,1000);
    w.show();
    w.pPaintPuzzle();
    //th1.join();
    return a.exec();
#endif
    //delete layout;

}

#endif



