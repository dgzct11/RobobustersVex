#pragma once
#include "main.h"
#include "Constants.hpp"
using namespace pros;
class Endgame{
    public: 
    Motor endgame = Motor(ENDGAME_PORT);
    Endgame(){
        endgame.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    void launch()
    {
        endgame.move(100);
    }
    void reverse(){
        endgame.move(-100);
    }
    void stop()
    {
        endgame.move_velocity(0);
    }
};
 