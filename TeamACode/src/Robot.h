#include "main.h"
#include "Drivetrain.h"
#include "Roller.h"

class Robot{
  public:
    Vector2 pos;
    Drivetrain drivetrain;
    Roller roller;
    Endgame endgame;

    Robot(Drivetrain drivetrain, Roller roller, Endgame endgame) : drivetrain(drivetrain), roller(roller), endgame(endgame){
      pos = drivetrain.pos;
    }

    double DistanceTo(Vector2 inpos){
      double xDistance = pos.x - inpos.x;
      double yDistance = pos.y - inpos.y;

      return sqrt(pow(xDistance,2) + pow(yDistance, 2));
    }

};

