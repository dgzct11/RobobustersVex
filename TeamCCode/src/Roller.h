#include "main.h"
using namespace pros;
extern int ROLLER_PORT, ROLLER_VOLTAGE;
class Roller{
    public: 
    Motor rollerMotor = Motor(ROLLER_PORT);
    Roller(){
        rollerMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    void spin()
    {
        rollerMotor.move(ROLLER_VOLTAGE);
    }
    void spinOpp()
    {
        rollerMotor.move(-ROLLER_VOLTAGE);
    }
    void stop()
    {
        rollerMotor.move_velocity(0);
    }
};
 