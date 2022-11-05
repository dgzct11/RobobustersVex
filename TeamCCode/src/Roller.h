#pragma once
#include "main.h"
#include "Constants.hpp"
using namespace pros;
class Roller{
    public: 
    Motor rollerMotor = Motor(ROLLER_PORT);
    Roller(){
        rollerMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    void spin()
    {
        rollerMotor.set_reversed(false);
        rollerMotor.move(ROLLER_VOLTAGE);
    }
    void spinOpp()
    {
        rollerMotor.set_reversed(true);
        rollerMotor.move(ROLLER_VOLTAGE);
    }
    void stop()
    {
        rollerMotor.move_velocity(0);
    }
};
 
