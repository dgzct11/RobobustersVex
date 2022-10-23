#pragma once
using namespace std;

#include "main.h"
#include <iostream>
#include "Utils.hpp"
#include <cmath>
 
class Arc{
    public:
    float radius;
    float dtheta;
    float arcL;
    float rtheta1;
    float rtheta2;
    Vector2 center;
    Vector2 I1;
    Vector2 I2;
    Arc(Vector2 I1, Vector2 P, Vector2 I2)
    {
        this->I1 = I1;
        this->I2 = I2;
        float d1 = dist(I1, P);
        //cout << "D1 " << d1 << endl;
        float d2 = dist(I1, I2);
        //cout << "D2 " << d2 << endl;
        dtheta = 2 * acosf((d2 / 2) / d1);
        radius = (d2 / 2) / sinf(dtheta / 2);
        arcL = radius * dtheta;
        rtheta1 = gATan(I1.y - P.y, I1.x - P.x);
        //cout << "t1 dy " <<  I1.y - P.y << endl;
        //cout << "t1 dx" << I1.x - P.x << endl;
        //cout << "theta1 " << rtheta1 * 180 / 3.14 << endl;
        rtheta2 = gATan(I2.y - P.y,  I2.x - P.x);
        //cout << "t2 dy " <<  I2.y - P.y << endl;
        //cout << "t2 dx" << I2.x - P.x << endl;
        //cout << "theta2 " << rtheta2 * 180 / 3.14 << endl;
        float thetaToCenter = (rtheta1 + rtheta2) / 2;
        //cout << "PtoCenter angle " << thetaToCenter * 180 / 3.14 << endl;
        float PtoCenter = (2 * radius * d1) / d2;
        //cout << "PtoCenter " << PtoCenter << endl;
        center = {P.x + PtoCenter * cos(thetaToCenter), P.y + PtoCenter * sin(thetaToCenter)};
        rtheta1 = gATan((I1.y - center.y), (I1.x - center.x));
        //cout << "theta1 " << rtheta1 * 180 / 3.14 << endl;
        rtheta2 = gATan((I2.y - center.y), (I2.x - center.x));
        //cout << "theta2 " << rtheta2 * 180 / 3.14 << endl;
    };

    float dist(Vector2 p1, Vector2 p2)
    {
        float x = abs(p1.x - p2.x);
        float y = abs(p1.y - p2.y);
        //cout << "x " << x << endl;
        //cout << "y " << y << endl;
        return sqrtf(powf(x, 2) + powf(y, 2));
    };

    Vector2 distanceToCoordinate(float distance)
    {
        float ntheta = distance / radius;
        Vector2 point;
        if(ntheta > dtheta)
        {
            return I2;
        }
        if(rtheta2 > rtheta1)
        {
            point = {center.x + cos(rtheta1 + ntheta) * radius, center.y + sin(rtheta1 + ntheta) * radius};
        }
        else {
            point = {center.x + cos(rtheta1 - ntheta) * radius, center.y + sin(rtheta1 - ntheta) * radius};
        }
        //cout << "nTheta" << ntheta * 180 / 3.14 << endl;
        return point;
    };

    float gATan(float y, float x)
    {
        float theta = atanf(y / x);
        if(theta < 0)
        {
            theta += 2 * 3.14;
        }
        if(y > 0 && x < 0)
        {
            theta -= 3.14;
        }
        else if(y < 0 && x < 0)
        {
            theta += 3.14;
        }
        return theta;
    }
};