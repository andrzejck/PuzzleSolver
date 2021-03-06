//
// Created by ar on 11.01.20.
//

#ifndef PUZZLE_PUZZLELIST_H
#define PUZZLE_PUZZLELIST_H

#include <vector>
#include "puzzle.h"
#include <algorithm>
#include <unordered_map>
#include <stdexcept>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/unordered_map.hpp>


bool comparePuzzle(Puzzle * l1, const Puzzle * l2);



static std::string IDS[] =  {"0|1", "2|3", "4", "5", "6|7",
                             "9", "10", "12", "13+11", "14+8",
                             "15", "16", "17", "18"};


class PuzzleList {
private:
    std::vector<Puzzle*> puzzleList;
    std::unordered_map<std::string, int> puzzleIds;
    std::unordered_map<std::string, Puzzle*> puzzleIdsMap;
    float minAngle;
    bool filled=false;
public:
    bool isFilled() const;

    float getMinAngle() const;

    float getMinSpan() const;

private:
    float minSpan;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        //ar & puzzleList;
        ar & puzzleIds;
        ar & minSpan;
        ar & minAngle;
    }
    void calculateMins(){
        minAngle=2*M_PI;
        minSpan=100000;
        for(auto p: puzzleList){
            if(minAngle > p->getMinAngle())
                minAngle = p->getMinAngle();
            if(minSpan > p->getMinSpan())
                minSpan = p->getMinSpan();
        }
    }

public:
    //PuzzleList();
    void generateSimplified();
//    void generateSimplified1();
//    void generateSimplified2();
//    void generate();
    void copyFrom(PuzzleList & pl){
        if(! puzzleList.empty()){
            throw std::logic_error("PuzzleList.copyFrom into not empty list");
        }
        puzzleIdsMap.clear();
        for(auto pid : puzzleIds){
            for(int i=0; i < pid.second; i++){
                puzzleList.push_back(pl.getById(pid.first));
                puzzleIdsMap[pid.first] = pl.getById(pid.first);
            }
        }
        filled = true;
    }

    std::vector<Puzzle*>::const_iterator cbegin(){
        return puzzleList.cbegin();
    }

    std::vector<Puzzle*>::const_iterator cend(){
        return puzzleList.cend();
    }

    const unsigned long size() const{
        return puzzleList.size();
    }

    Puzzle * get(int pos) const{
        return puzzleList[pos];
    }

    void erase(int pos){
        puzzleIds[puzzleList[pos]->getId()]--;
        if (puzzleIds[puzzleList[pos]->getId()] == 0){
            puzzleIds.erase(puzzleList[pos]->getId());
            puzzleIdsMap.erase(puzzleList[pos]->getId());

        }
        puzzleList.erase(puzzleList.begin() + pos);


    }

    bool operator==(const PuzzleList &rhs) const;

    bool operator!=(const PuzzleList &rhs) const;

    void random_shuffle(){
        std::random_shuffle(puzzleList.begin(), puzzleList.end());
    }

    void print(){
        for(auto p: puzzleList){
            std::cout<<p->getId() << " ";
        }
        std::cout << std::endl;
    }

    void sort(){
        std::sort(puzzleList.begin(), puzzleList.end(), comparePuzzle);
    }

    const std::string hash(){
        std::string res;
        //int tmp=puzzleIds[res];
        for(std::string id: IDS){
            if(puzzleIds.count(id) > 0){
                res.append(id);
                res.append(std::to_string(puzzleIds[id]));
            }
        }
        return res;
    }

    Puzzle * getById(std::string id){
        if(puzzleIdsMap.count(id) >= 0){
            return puzzleIdsMap[id];
        }else
            return nullptr;

    }
    void clear(){
        puzzleList.clear();
        puzzleList.shrink_to_fit();
        puzzleIds.clear();
        puzzleIdsMap.clear();

    }
};


#endif //PUZZLE_PUZZLELIST_H
