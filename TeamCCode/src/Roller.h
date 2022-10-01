#include "main.h"
using namespace pros;
extern int ROLLER_PORT, ROLLER_VOLTAGE;
class Roller{
    public: 
    Motor rollerMotor = Motor(ROLLER_PORT);
    void spin()
    {
        rollerMotor.move(ROLLER_VOLTAGE);
    }
};
 