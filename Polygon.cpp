//
// Created by ar on 14.01.20.
//

#include "Polygon.h"

void Polygon::setColor(const Qt::GlobalColor &color) {
    Polygon::color = color;
}

Qt::GlobalColor Polygon::getColor() const {
    return color;
}