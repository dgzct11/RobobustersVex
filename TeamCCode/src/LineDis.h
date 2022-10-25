#pragma once
#include <iostream>
#include <cmath>
#include "Utils.hpp"
class Line{
    public:
    double x1, y1, x2, y2, ratio, disBtwnCords, disToCordx, disToCordy;
    Vector2 startPos;
    Vector2 endPos;
    Line(Vector2 startPos, Vector2 endPos){
      this->startPos = startPos;
      this->endPos = endPos;
    }
    Vector2 distanceToCoordinate(double dis){
      Vector2 disToCord = endPos.operator-(startPos);
      disToCordx = pow(disToCord.x, 2);
      disToCordy = pow(disToCord.y, 2);
      disBtwnCords = sqrt(disToCord.x + disToCord.y);
      ratio = dis/disBtwnCords;
      disToCord.x *= ratio;
      disToCord.y *= ratio;
      return disToCord;
    }
};