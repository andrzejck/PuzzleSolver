//
// Created by ar on 19.02.20.
//

#ifndef PUZZLE_LAYOUTCACHEIMAGE_H
#define PUZZLE_LAYOUTCACHEIMAGE_H

#include "Layout.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class LayoutCacheImage {
private:
    int points;
    float sumArea;
    float sumEnvelope;
    int puzzle;
    float sumAngles;
    std::string puzzleListHash;
public:
    float getSumAngles() const {
        return sumAngles;
    }

private:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & points;
        ar & sumArea;
        ar & sumEnvelope;
        ar & puzzle;
        ar & sumAngles;
        ar & puzzleListHash;

    }

public:
    const std::string &getPuzzleListHash() const {
        return puzzleListHash;
    }

public:

    const int pointsCount() const{
        return points;
    }

    const float getSumArea()  const{
        return sumArea;
    }

    const float getSumEnvelope()  const{
        return sumEnvelope;
    }

    const float puzzleCount()  const{
        return puzzle;
    }

    LayoutCacheImage(){
        points = 0;
        sumArea = 0;
        sumEnvelope = 0;
        puzzle = 0;
    }

    LayoutCacheImage(const Layout & l, PuzzleList & pl){
        points=l.pointsCount();
        sumArea=l.getSumArea();
        sumEnvelope = l.getSumEnvelope();
        puzzle = l.puzzleCount();
        sumAngles = l.anglesSum();
        puzzleListHash = pl.hash();

    }

    bool operator==(const LayoutCacheImage &rhs) const {
        return //static_cast<const Polygon &>(*this) == static_cast<const Polygon &>(rhs) &&
                (int)(sumArea) == (int)(rhs.sumArea) &&
                (int)(sumEnvelope/5) == (int)(rhs.sumEnvelope/5) &&
                pointsCount()  == rhs.pointsCount() &&
                puzzleCount() == rhs.puzzleCount() &&
                getSumAngles() == rhs.getSumAngles() &&
                getPuzzleListHash() == rhs.getPuzzleListHash();

    }

    bool operator!=(const LayoutCacheImage &rhs) const {
        return !(*this == rhs);
    }

};

class LayoutCacheImageHashFunction {
public:

    // Use sum of lengths of first and last names
    // as hash function.
    size_t operator()(const LayoutCacheImage& l) const
    {
        return (int)(l.getSumArea())+(int)(l.getSumEnvelope()/10)+l.pointsCount()+l.puzzleCount();
    }
};

#endif //PUZZLE_LAYOUTCACHEIMAGE_H
