//
// Created by ar on 14.01.20.
//

#ifndef PUZZLE_POLYGON_H
#define PUZZLE_POLYGON_H


#include <QtCore/QPointF>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Polygon {
private:
    Qt::GlobalColor color;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & color;
    }
public:
    void setColor(const Qt::GlobalColor &color);

public:
    virtual  QPointF * asQPointF(float scale, float ox, float oy) = 0;
    virtual unsigned long pointsCount() const = 0;

    Qt::GlobalColor getColor() const;
};



#endif //PUZZLE_POLYGON_H
