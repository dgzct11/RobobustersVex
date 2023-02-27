#pragma once

#include "pros/motors.hpp"
#include "../Constants.hpp"

using namespace pros;
using namespace Constants;

class Intake {
    private:
        Motor intkL = Motor(intakeL_p);
        Motor intkR = Motor(intakeR_p);
        Motor_Group intk = Motor_Group({intkL, intkR});
    public:
        Intake() {
            intk.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        }
        inline void move(signed char voltage) {
            intk.move(voltage);
        }
};