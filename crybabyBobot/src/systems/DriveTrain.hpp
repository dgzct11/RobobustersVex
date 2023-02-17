#pragma once

#include "../Constants.hpp"
#include "pros/motors.hpp"

using namespace Constants;
using namespace pros;

struct DriveTrain {
    Motor fl_mtr = Motor(fl_p, true);
    Motor bl_mtr = Motor(bl_p, true);
    Motor fr_mtr = Motor(fr_p);
    Motor br_mtr = Motor(br_p);

    Motor_Group left_g =  Motor_Group({fl_mtr, bl_mtr});
    Motor_Group right_g = Motor_Group({fr_mtr, br_mtr});

    std::function<void(void)> teleMove;

    DriveTrain() {
        left_g.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        right_g.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        //left_g.set_reversed(true);
   
        left_g.tare_position();
        right_g.tare_position();
    }

    inline void tankDrive(signed char leftY, signed char rightY){
        left_g.move(abs(leftY)<threshold ? 0 :leftY);
        right_g.move(abs(rightY)<threshold ? 0 :rightY);
    }

    inline void arcadeDrive(signed char leftY, signed char rightX) {
        leftY = abs(leftY)<threshold ? 0 : leftY;
        rightX = abs(rightX)<threshold ? 0 : rightX;
        left_g.move(leftY + rightX);
        right_g.move(leftY - rightX);
    }
};
