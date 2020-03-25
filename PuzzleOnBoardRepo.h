//
// Created by ar on 24.03.2020.
//

#ifndef PUZZLE_PUZZLEONBOARDREPO_H
#define PUZZLE_PUZZLEONBOARDREPO_H
#include "PuzzleOnBoard.h"
#include <boost/unordered_map.hpp>



class PuzzleOnBoardRepo {
private:
    boost::unordered_map<std::size_t, PuzzleOnBoard*> repo;
public:
    int miss=0;
    int hit=0;

    PuzzleOnBoard * get(std::size_t hash){
        if(repo.count(hash) > 0) {
            hit++;
            return repo[hash];
        }else {
            miss++;
            return nullptr;
        }
    }

    PuzzleOnBoard * get(std::string puzzleId_,
                        int x,
                        int y,
                        int pivotPointId_,
                        bool isFlipped_){
        return get(PuzzleOnBoard::hash_value(puzzleId_,
                x,
                y,
                pivotPointId_,
                isFlipped_));
    }

    PuzzleOnBoard * set(std::size_t hash, PuzzleOnBoard* p){
        repo[hash] = p;
    }

    int getSize() {return repo.size();}

    ~PuzzleOnBoardRepo(){
        for(auto element : repo){
            delete element.second;
        }
    }
};


#endif //PUZZLE_PUZZLEONBOARDREPO_H
