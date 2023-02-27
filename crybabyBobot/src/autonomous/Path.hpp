#pragma once

#include "../Constants.hpp"
#include "Line.hpp"
#include "Vector2.hpp"
#include <cstdlib>
#include <math.h>

class Path {
    public:
        Vector2* pPoints;
        unsigned short n;

        Vector2* nPoints;
    private:
        Line* lines;

        double* distAtPoint;
        double* headingAtPoint;
        
        Vector2* sPoints;

        double* radius;
        double* curvature;
        double* oVel;
        double* nVel;
        double* vel = new double[2];

        static constexpr double k = 5;
        static constexpr double deltaTime = 0.005;
        static constexpr double maxRate = 5;
        static constexpr double maxChange = deltaTime*maxRate;
        static constexpr double lookaheadRadius = 15;

        double rateOutput;
        unsigned short currentSegment = 0;
        Vector2 lookaheadPoint;

        void createPath() {
            unsigned short pNum = 0;
            unsigned short pNumL[n-1];
            lines = (Line*)malloc(sizeof(Line)*(n-1));
            for (unsigned short i = 0; i < n-1; i++) {
                lines[i] = Line(pPoints[i], pPoints[i+1]);
                pNumL[i] = lines[i].disBtwnCords/spacing;
                pNum += pNumL[i];
            }

            nPoints = (Vector2*)malloc(sizeof(Vector2)*(pNum+1));
            pNum = 0;

            for (unsigned short i = 0; i < n-1; i++) {
                for (unsigned short v = 0; v < pNumL[i]; v++) {
                    //Point injection given spacing
                    nPoints[pNum+v] = lines[i].ratioToCoordinate(((double)v)/pNumL[i]);
                }
                pNum += pNumL[i];
            }

            nPoints[pNum] = lines[n-2].endPos;
            n=pNum;
                
            nPoints = smoother(nPoints, 1, 1, 100);
            
            free(lines);
            lines = (Line*)malloc(sizeof(Line)*(n-1));
            distAtPoint = new double[n];
            headingAtPoint = new double[n];
            radius = new double[n-3];
            curvature = new double[n-3];
            oVel = new double[n-3];
            nVel = new double[n-3];

            unsigned short v,h;
            double k1,k2,a,b;
            double x1,x2,xx2,x3,y1,y2,yy2,y3;

            distAtPoint[0] = 0;
            headingAtPoint[0] = 0;

            for (unsigned short i = 0; i < n-1; i++) {
                lines[i] = Line(nPoints[i], nPoints[i+1]);
                distAtPoint[i+1] = distAtPoint[i] + lines[i].disBtwnCords;
                headingAtPoint[i+1] = headingAtPoint[i] + nPoints[i].headingTo(headingAtPoint[i], nPoints[i+1]);
                if (i<n-3) {
                    v=i+1; h=v+1;

                    x1=nPoints[i].x; x2=nPoints[v].x; x3 = nPoints[h].x;
                    y1=nPoints[i].y; y2=nPoints[v].y; y3 = nPoints[h].y;
                    xx2 = x2*x2; yy2= y2*y2;
                    
                    k1 = 0.5 * (x1*x1 + y1*y1 - xx2 - yy2) * (x1 - x2);
                    k2 = (y1-y2)/(x1-x2);
                    b = 0.5 * (xx2 - 2*x2*k1 + yy2 - x3*x3 + 2*x3*k1 -
                        y3*y3) / (x3*k2 - y3 + y2 - x2*k2);
                    a = k1 - k2*b;

                    radius[i] = nPoints[i].distanceTo(Vector2(a,b));
                    curvature[i]=1/radius[i];
                    
                    oVel[i]=fmin(maxRelVel, k/curvature[i]);
                }
            }
            for (unsigned short i = 0; i < n-4; i++) {
                nVel[i]=fmin(oVel[i], sqrt(oVel[i+1]*oVel[i+1] + 2*accel*lines[i].disBtwnCords));
            }
            nVel[n-4]=oVel[n-4];
            lookaheadPoint = nPoints[0];
        }

        Vector2* smoother(Vector2* path, double a, double b, double tolerance) {
            sPoints = path;
            double change = tolerance;
            while(change >= tolerance) {
                change = 0.0;
                for(unsigned short i=1; i<n-1; i++) {
                    double aux = sPoints[i].x;
                    double auy = sPoints[i].y;
                    sPoints[i] = sPoints[i] + Vector2(a * (nPoints[i].x - 
                        sPoints[i].x) + b * (sPoints[i-1].x + sPoints[i+1].x -
                        (2.0 * sPoints[i].x)),
                        a * (nPoints[i].y - sPoints[i].y) + b * (sPoints[i-1].y +
                        sPoints[i+1].y - (2.0 * sPoints[i].y)));
                    change += fabs(aux - sPoints[i].x);
                }
            }
            return sPoints;
        }
        
        double rateLimiter(double input) {
            rateOutput += constrain(input-rateOutput, -maxChange, maxChange);
            return rateOutput;
        }

        void findTargetPoint(Vector2 pos) {
            for (;currentSegment<n-1;currentSegment++) {
                Vector2 f = lines[currentSegment].startPos - pos;
                Vector2 d = lines[currentSegment].dvec;
                double a = d.dotProduct(d);
                double b = 2 * f.dotProduct(d);
                double c = f.dotProduct(f) - lookaheadRadius*lookaheadRadius;
                double discriminant = b*b - 4*a*c;
                if (discriminant > 0) {
                    discriminant = sqrtf(discriminant);
                    double t1 = (-b-discriminant)/(2*a);
                    double t2 = (-b+discriminant)/(2*a);
                    if (0 <= t1 && t1 <= 1) {
                        if (0 <= t2 && t2 <= 1) {
                            lookaheadPoint = (t1 > t2) ? lines[currentSegment].ratioToCoordinate(t1) : lines[currentSegment].ratioToCoordinate(t2);
                            break;
                        } else {
                            lookaheadPoint = lines[currentSegment].ratioToCoordinate(t1);
                            break;
                        } 
                    } else if (0 <= t2 && t2 <= 1) {
                        lookaheadPoint = lines[currentSegment].ratioToCoordinate(t2);
                        break;
                    }
                }
            }
        }

        
    public:
        Path(Vector2* pPoints, unsigned short n):pPoints(pPoints),n(n){
            createPath();
        };
        ~Path(){
            free(nPoints);
            free(lines);
            delete[] distAtPoint;
            delete[] headingAtPoint;
            delete[] radius;
            delete[] curvature;
            delete[] oVel;
            delete[] nVel;
            delete[] vel;
        }


        double* findRobotVelocities(Vector2 pos, double heading) {
            findTargetPoint(pos);
            Vector2 dvec = lookaheadPoint-pos;
            double curvature = (dvec.x * 2) / (dvec.x * dvec.x + dvec.y * dvec.y);
            signed char side = signum(sin(heading)*(dvec.x)-cos(heading)*(dvec.y));
            double sigCurve = side*curvature;
            vel[0] = maxRelVel*(2+sigCurve*trackwidth)/2;
            vel[1] = maxRelVel*(2-sigCurve*trackwidth)/2;
            return vel;
        }
};
