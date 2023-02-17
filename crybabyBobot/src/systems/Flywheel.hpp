#pragma once

#include "pros/motors.hpp"
#include "../Constants.hpp"

using namespace pros;
using namespace Constants;

class Flywheel {
    private:
        Motor fly = Motor(fly_p);
    public:
        Flywheel() {
            fly.set_brake_mode(E_MOTOR_BRAKE_HOLD);
        }
        inline void move(signed char voltage) {
            fly.move(voltage);
        }
};