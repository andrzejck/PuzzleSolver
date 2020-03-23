//
// Created by ar on 23.03.2020.
//

#ifndef PUZZLE_MATH_H
#define PUZZLE_MATH_H
#include <unordered_map>
#include <bits/stdc++.h>

//#define MEASURE true
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class Math {
    std::unordered_map<std::pair<int,int>, float, hash_pair> atanCache;
    long hits=0;
    long mises=0;
public:
    static float ApproxAtan2(float y, float x);
    static float ApproxAtan(float z);
    float ApproxAtan2Cache(int y, int x){
        auto yx = std::make_pair(y,x);
        if (atanCache.count(yx) > 0) {
#ifdef MEASURE
            hits++;
#endif
            return atanCache[yx];
        }else{
#ifdef MEASURE
            mises++;
#endif
            float atan2=ApproxAtan2(y,x);
            atanCache[yx] = atan2;
            return atan2;
        }


    };
    void printStatistics(){
        //std::cout <<  " hits+mises " <<  (mises+hits) <<  " hits/mises " << ((float)hits/(float)mises) << " cacheSize " << atanCache.size() <<  std::endl;
    }
};


#endif //PUZZLE_MATH_H
