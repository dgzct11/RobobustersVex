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

    void spin(int x){
        flywheel.move_velocity(x);
    }

    void spinReverse(int x){
        flywheel.move_velocity(x);
    }

    void stop(){
        flywheel.move_velocity(0);
    } 
};