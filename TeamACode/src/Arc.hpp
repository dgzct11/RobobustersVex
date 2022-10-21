#pragma once

#include "main.h"
#include "Constants.hpp"
#include "Utils.hpp"

using namespace pros;
class Arc{
    public:
    float radius;
    float dtheta;
    float arcL;

    Arc(Vector2 I1, Vector2 P, Vector2 I2)
    {
        float d1 = dist(I1, P);
        float d2 = dist(I1, I2);
        dtheta = 2 * acosf((d2 / 2) / d1);
        radius = (d2 / 2) / tanf(dtheta);
        arcL = radius * dtheta;
    };

    float dist(Vector2 p1, Vector2 p2)
    {
        return sqrtf(powf(p1.x - p2.x, 2.0) + powf(p1.y - p2.y, 2.0));
    };

    Vector2 distanceToCoordinate(float distance)
    {
        float ntheta = distance / radius;

    };
};