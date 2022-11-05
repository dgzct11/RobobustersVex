#pragma once
#include "main.h"
#include "Constants.hpp"
#include "pros/motors.h"
using namespace pros;
class Launcher{
    public:
    Motor launcherMotor = Motor(LAUNCHER_PORT);
    Motor releaseMotor = Motor(RELEASE_PORT);

    Launcher(){
        releaseMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        launcherMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }
    void trigger(){
        launcherMotor.move(200);
    }
    void hold(){
        launcherMotor.move_velocity(0);
    }
    
    void release(){
        releaseMotor.move(200);
    }
    void holdRelease(){
        releaseMotor.move_velocity(0);
    }
};