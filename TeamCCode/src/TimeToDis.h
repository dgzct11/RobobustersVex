#include <cmath>
class TimeToPosition {
private:
  double a1;
  double a2;
  double maxV;
  double dt1;
  double dt2;
  double dt3;
  double d1;
  double d2;
  double d3;

public:
  TimeToPosition(double a1, double a2, double maxV, double dt2) {
    this->a1 = a1;
    this->a2 = a2;
    this->maxV = maxV;
    dt1 = maxV / a1;
    this->dt2 = dt2;
    dt3 = fabs(maxV / a2);
    d1 = maxV * dt1 * .5;
    d2 = maxV * dt2 + d1;
    d3 = maxV * dt3 * .5 + d2;
  }

  double timeToDis(double t) {
    if (t >= dt3 + dt2 + dt1)
      return d3;
    else if (t > dt2 + dt1)
      return d2 + (.5*(t-dt1-dt2) * (2*maxV + a2*(t - dt1 - dt2)));
    else if (t == dt2 + dt1)
      return d2;
    else if (t > dt1)
      return d1 + (maxV * (t - dt1));
    else if (t == dt1)
      return d1;
    return .5 * a1 * pow(t, 2);
  }

  //in case we move to other class 
  double timeToDis(double a1, double a2, double maxV, double dt2, double t) 
  {
    double dt1 = maxV / a1;
    double dt3 = fabs(maxV / a2);
    double d1 = maxV * dt1 * .5;
    double d2 = maxV * dt2 + d1;
    double d3 = maxV * dt3 * .5 + d2;
    
    if (t >= dt3 + dt2 + dt1)
      return d3;
    else if (t > dt2 + dt1)
      return d2 + (.5*(t-dt1-dt2) * (2*maxV + a2*(t - dt1 - dt2)));
    else if (t == dt2 + dt1)
      return d2;
    else if (t > dt1)
      return d1 + (maxV * (t - dt1));
    else if (t == dt1)
      return d1;
    return .5 * a1 * pow(t, 2);
  }

};