#pragma once

#include "pros/motors.hpp"
#include "../Constants.hpp"

using namespace pros;
using namespace Constants;

class Intake {
    private:
        Motor intakeL = Motor(intakeL_p);
        Motor intakeR = Motor(intakeR_p);
        Motor_Group intake = Motor_Group({intakeL, intakeR});
    public:
        Intake() {
            intake.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        }
        inline void move(signed char voltage) {
            intake.move(voltage);
        }
};