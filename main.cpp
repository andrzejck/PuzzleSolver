//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN
#define MAIN
#define BOOST_TEST_MODULE My Test

#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include "PuzzleList.h"

#include "CIniFile.h"
#include <thread>

#include <algorithm>

#include "Solver.h"






CIniFile * CIniFile::instance = nullptr;
//std::string s= std::string("QUEUE_SIZE");
//int QUEUE_SIZE = 1000000;
int QUEUE_SIZE = 100000;
bool SAVE_AFTER_LIMIT = true;

PuzzleList pl;
#define SHOW_WINDOW 1
#define REPORT_TRESHOLD 13
#define LAYOUT_POINT_TRESHOLD 5000

//#define SAVE_AFTER_LIMIT false
#define COUT(x) std::cout << x << std::endl;
#define DEBUG_FIT (fgIterations < 0)
#define DEBUG (fgIterations < 0)
#define DEBUG_PROMISSING (fgIterations <= 0)
#define DEBUG_INTERLACE (fgIterations <=  0)
#define SAVE_PRE false
//#define FGITERATIONSSTART 2433636
//#define READ_FROM_FILE "700000savelog_layout"
#define SAVELOG 20000000





#define LAMBDA -1
#define FITSCALE 1
//std::random_device rd;
//std::mt19937 g(rd());
std::set<int> skipIt;









//std::stack<std::pair<Layout, PuzzleList>> layoutStack;
//std::vector<std::pair<Layout, PuzzleList>> layoutStack;


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








bool finish = false;

long iterations=0;














//namespace logging = boost::log;
void solvePuzzles( MainWindow * w, QString layoutFilename, int iStart=-1, int iSize = -1 ){
    CIniFile * cIniFile = cIniFile->getInstance();
    Solver solver;
    SolverConfig solverConfig;
    solverConfig.QUEUE_SIZE = cIniFile->get<int>(std::string("QUEUE_SIZE"));
    solverConfig.SAVE_AFTER_LIMIT = cIniFile->get<bool>(std::string("SAVE_AFTER_LIMIT"));
    solverConfig.CLEAR_LAYOUT_PUZZLE_LIST = cIniFile->get<bool>(std::string("CLEAR_LAYOUT_PUZZLE_LIST"));
    solverConfig.INITIAL_LAYOUT_NOT_EMPTY = cIniFile->get<bool>(std::string("INITIAL_LAYOUT_NOT_EMPTY"));
    solver.setSolverConfig(solverConfig);
    solver.solvePuzzles(w,layoutFilename,iStart,iSize);
}
#ifdef MAIN
int main(int argc, char *argv[])
{
    //logging::add_file_log("layout.log");
    QString layoutFilename;
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
    th1.detach();
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



