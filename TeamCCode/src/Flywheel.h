#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;

class Flywheel{
    public:
    Motor flywheel = Motor(FLYWHEEL);

    Flywheel(){
    }

    void spin(){
        flywheel.move(100);
    }

    void spinReverse(){
        flywheel.move(-100);
    }

    void stop(){
        flywheel.move_velocity(0);
    } 
};