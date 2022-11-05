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
        releaseMotor.move_relative(500,100);
        delay(200);
        launcherMotor.move_relative(500,100);
    }
    void back(){
        launcherMotor.move_relative(0,100);
    }
    void hold(){
        releaseMotor.move_velocity(0);
        launcherMotor.move_velocity(0);
    }
};