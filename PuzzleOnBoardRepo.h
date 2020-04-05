//
// Created by ar on 24.03.2020.
//

#ifndef PUZZLE_PUZZLEONBOARDREPO_H
#define PUZZLE_PUZZLEONBOARDREPO_H
#include "PuzzleOnBoard.h"
//#include <boost/unordered_map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/unordered_map.hpp>



class PuzzleOnBoardRepo {
private:
    std::unordered_map<std::string, PuzzleOnBoard*> repo;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & repo;
    }

public:
    int miss=0;
    int hit=0;

    PuzzleOnBoard * get(std::string hash){
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
                        bool isFlipped_,
                        float angle_,
                        const Puzzle * puzzle_){
        PuzzleOnBoard * ret =  get(PuzzleOnBoard::hash_value(puzzleId_,
                x,
                y,
                pivotPointId_,
                isFlipped_,
                angle_));
        if(ret != nullptr)
            ret->setPuzzle(puzzle_);
        return ret;
    }

    PuzzleOnBoard * set(std::string hash, PuzzleOnBoard* p){
        repo[hash] = p;
    }

    int getSize() {return repo.size();}

    ~PuzzleOnBoardRepo(){
        for(auto element : repo){
            delete element.second;
        }
    }

    PuzzleOnBoard * getOrConstruct(PuzzleList & puzzleListRepo,
                                   std::string puzzleId_,
                                   int x,
                                   int y,
                                   int pivotPointId_,
                                   bool isFlipped_,
                                   float angle_){
        PuzzleOnBoard * puzzleOnBoard;
        Puzzle * puzzle=puzzleListRepo.getById(puzzleId_);

        puzzleOnBoard = get(puzzleId_,
                            x,
                            y,
                            pivotPointId_,
                            isFlipped_,
                            angle_,
                            puzzle);



        if(puzzleOnBoard == nullptr){

            puzzleOnBoard = new PuzzleOnBoard(puzzle,
                                              Point(0, 0),
                                              0, true, 0);
            puzzleOnBoard->reset();
            if(isFlipped_){
                puzzleOnBoard->flip();
            }
            puzzleOnBoard->rotate(angle_, pivotPointId_);
            puzzleOnBoard->translate(Point(x,y));
            puzzleOnBoard->setInRepository();
            set(puzzleOnBoard->hash_value(), puzzleOnBoard);
        }

    }
};


#endif //PUZZLE_PUZZLEONBOARDREPO_H
