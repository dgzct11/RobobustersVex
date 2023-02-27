#pragma once

#include "pros/motors.hpp"
#include "../Constants.hpp"

using namespace pros;
using namespace Constants;

class Indexer {
    private:
        Motor indx = Motor(indx_p);
    public:
        Indexer() {
            indx.set_brake_mode(E_MOTOR_BRAKE_HOLD);
            indx.tare_position();
        }
        inline void launch() {
            indx.move_absolute(100 ,50);
        }
        inline void reset() {
            indx.move_absolute(0, 50);
        }
};