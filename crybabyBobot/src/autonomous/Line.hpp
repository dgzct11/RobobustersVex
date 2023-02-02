#pragma once

#include "Vector2.hpp"

class Line{
    public:
    Vector2 startPos, endPos, dvec;
    double disBtwnCords;

    Line(Vector2 startPos, Vector2 endPos):startPos(startPos),endPos(endPos) {
      dvec = endPos-startPos;
      disBtwnCords = startPos.distanceTo(endPos);
    }

    Vector2 ratioToCoordinate(double ratio){
      return Vector2(dvec.x * ratio + startPos.x, dvec.y * ratio + startPos.y);
    }
};