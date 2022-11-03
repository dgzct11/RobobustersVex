#include <cmath>
#include <iostream>
class TimeToPosition {
private:
  double a1;
  double a2;
  double maxV;
  double totalDis;
  double dt1;
  double dt2;
  double dt3;
  double dd1;
  double dd2;
  double dd3;

  public:
    //will be setConst in final
    TimeToPosition(double dis, double a1, double a2, double maxV) {
    totalDis = dis;
    this->a1 = a1;
    this->a2 = a2;
    this->maxV = maxV;
    dt1 = maxV / a1;
    dt3 = fabs(maxV / a2);
    dd1 = maxV * dt1 * .5;
    dd3 = maxV * dt3 * .5;
    dd2 = totalDis - dd1 - dd3;
    dt2 = dd2/maxV;
  }

  double timeToDis(double t) 
  {
      
    if (t >= dt3 + dt2 + dt1)
      return totalDis;
    else if (t > dt2 + dt1){
      double time = t - dt2 - dt1;
      return dd1 + dd2 + (.5*time*((2*maxV) +(a2 *time)));
    }
    else if (t == dt2 + dt1)
      return dd1 + dd2;
    else if (t > dt1)
      return dd1 + (maxV * (t - dt1));
    else if (t == dt1)
      return dd1;
    return .5 * a1 * pow(t, 2);
  }

};
