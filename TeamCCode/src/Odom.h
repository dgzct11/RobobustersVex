#pragma once
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;

class Odom{
    public:
    ADIEncoder back = ADIEncoder(BACK_ODOM_1, BACK_ODOM_2, false);

    /*Odom(){
        back.reset();
    }*/

    int getValue(){
        return back.get_value();
    }  

    void reset(){
        back.reset();
    }

};