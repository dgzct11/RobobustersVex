#pragma once
#include "main.h"
#include "Constants.hpp"
#include "pros/motors.h"
using namespace pros;
class Launcher{
    public:
    Motor launcherMotor = Motor(LAUNCHER_PORT);
    Launcher(){
        launcherMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    void trigger(){
        launcherMotor.move_velocity(100);
    }
    void hold(){
        launcherMotor.move_velocity(0);
    }
};