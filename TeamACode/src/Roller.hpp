#pragma once

#include "main.h"
#include "Constants.hpp"

using namespace pros;
class Roller{
    public:
    Motor roller = Motor(ROLLER_MOTOR_PORT);
   
    void spin(int voltage)
    {
        roller.move(voltage);
    }
    
    void stop()
    {
        roller.move(0);
    }

    void step(){
	roller.move_relative(45,127);
    }
};
