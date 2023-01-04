#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;

class Intake{
    public:
    Motor intakeRight = Motor(INTAKE_RIGHT, MOTOR_GEARSET_6);
    Motor intakeLeft = Motor(INTAKE_LEFT, MOTOR_GEARSET_6, true);
    Motor_Group intake = Motor_Group({intakeRight, intakeLeft});

    void Spin(){
        intake.move(-127);
    }
    void SpinOpp(){
        intake.move(127);
    }
    void Stop(){
        intake.move(0);
    }
};