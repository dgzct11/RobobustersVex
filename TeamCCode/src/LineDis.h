#pragma once

#include <iostream>
#include <cmath>
#include "Utils.hpp"
class Line{
    public:
    double x1, y1, x2, y2, ratio, disBtwnCords, disToCordx, disToCordy;
    Vector2 startPos;
    Vector2 endPos;
    Vector2 disToCord;
    Line(Vector2 startPos, Vector2 endPos){
      this->startPos = startPos;
      this->endPos = endPos;
    }
    Vector2 distanceToCoordinate(double dis){
      disToCord = endPos.operator-(startPos);
      disToCordx = pow(disToCord.x, 2);
      disToCordy = pow(disToCord.y, 2);
      disBtwnCords = sqrt(disToCordx + disToCordy);
      ratio = dis/disBtwnCords;
      disToCord.x = disToCord.x * ratio + startPos.x;
      disToCord.y = disToCord.y * ratio + startPos.y;
      return disToCord;
    }
};
