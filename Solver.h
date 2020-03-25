//
// Created by ar on 22.03.2020.
//

#ifndef PUZZLE_SOLVER_H
#define PUZZLE_SOLVER_H

#include <mainwindow.h>
#include <QString>
#include <chrono>
#include <stack>
#include <queue>
#include <unordered_map>
#include "LayoutCacheImage.h"
#include <chrono>
#include <set>
#include <random>
#include <thread>


#define COUT(x) std::cout << x << std::endl;

#define DEBUG_FIT (fgIterations < 0)
#define DEBUG (fgIterations < 0)
#define DEBUG_PROMISSING (fgIterations <= 0)
#define DEBUG_INTERLACE (fgIterations <=  0)
#define SAVE_PRE false

#define SAVELOG 20000000
#define MAX_BUCKETS 100

struct SolverConfig{
    int QUEUE_SIZE;
    bool SAVE_AFTER_LIMIT;
    bool CLEAR_LAYOUT_PUZZLE_LIST;
    bool INITIAL_LAYOUT_NOT_EMPTY;
};





class Solver {
    struct CompareLayoutsClass{
        bool operator() (std::pair<Layout,PuzzleList> & l1, std::pair<Layout,PuzzleList> & l2){
            return CompareLayouts(l2,l1);
        }
    };
private:
    SolverConfig solverConfig;

    void process_mem_usage(double& vm_usage, double& resident_set){
        vm_usage     = 0.0;
        resident_set = 0.0;

        // the two fields we want
        unsigned long vsize;
        long rss;
        {
            std::string ignore;
            std::ifstream ifs("/proc/self/stat", std::ios_base::in);
            ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
                >> ignore >> ignore >> vsize >> rss;
        }

        long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
        vm_usage = vsize / 1024.0;
        resident_set = rss * page_size_kb;
    }

public:
    void setSolverConfig(const SolverConfig &solverConfig);

private:
    std::clock_t prevClock;
    std::vector<int> randomVect(int r){
        std::vector<int> res(r);
        std::iota (std::begin(res), std::end(res), 0);
        //std::random_shuffle(std::begin(res), std::end(res));
        return res;
    }
    int cache_hits = 0;
    int cache_misses = 0;
    long stackSize = 0;
    //auto rng = std::default_random_engine {};
    long fgIterations=0;
    long fcIterations=0;
    float maxArea =0;
    std::unordered_map<int, std::priority_queue<std::pair<Layout, PuzzleList>, std::vector<std::pair<Layout, PuzzleList>>, CompareLayoutsClass>> layoutStackBuckets;
    //std::priority_queue<std::pair<Layout, PuzzleList>, std::vector<std::pair<Layout, PuzzleList>>, CompareLayoutsClass> layoutStack;
    std::unordered_map<LayoutCacheImage, int, LayoutCacheImageHashFunction> layoutSet;
    void paintLayout(Layout & layout, QString filename, MainWindow * w){
        w->setLayout(&layout);
        w->pPaintPuzzle();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        w->grab().save(filename);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    void  push_back_to_stack(std::pair<Layout, PuzzleList> p);
    std::pair<Layout, PuzzleList>  top_stack();
    static bool CompareLayouts (const std::pair<Layout,PuzzleList> & l1, const std::pair<Layout,PuzzleList> & l2) {
//    if(l1.first.getQualityFactor() == l2.first.getQualityFactor()) {
//        return l1.first.pointsCount() < l2.first.pointsCount();
//    }else {
//        return (float) (l1.first.getQualityFactor())  >
//               (float) (l2.first.getQualityFactor()) ;
//    }
//    return l1.first.pointsCount() < l2.first.pointsCount();

    if(l1.first.pointsCount() == l2.first.pointsCount()) {
        return l1.first.getSumArea() > l2.first.getSumArea();
        //return l1.first.getQualityFactor() > l2.first.getQualityFactor();
    }else {
        return l1.first.pointsCount() < l2.first.pointsCount() ;
    }

}

public:
    void solvePuzzles( MainWindow * w, QString layoutFilename, int iStart=-1, int iSize = -1 );
    bool layNewPuzzle2(Layout &layout, PuzzleList &puzzles, MainWindow *w);
    void printBuckets();

    //~Solver();
};



#endif //PUZZLE_SOLVER_H
