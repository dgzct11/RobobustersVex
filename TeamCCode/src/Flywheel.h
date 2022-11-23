#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;

class Flywheel{
    public:
    Motor leftFlywheel = Motor(FLYWHEEL_LEFT);
    Motor rightFlywheel = Motor(FLYWHEEL_RIGHT);
    Motor_Group flywheel = Motor_Group({leftFlywheel,rightFlywheel});

    Flywheel(){
        leftFlywheel.set_reversed(true);
    }

    void spin(){
        flywheel.move(200);
    }

    void spinReverse(){
        flywheel.move(-600);
    }

    void stop(){
        flywheel.move_velocity(0);
    } 
};