#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
#include <string.h>
#include <bits/stdc++.h>

using namespace pros;

class Indexer{
    public:
    Motor indexer = Motor(INDEXER);

    Indexer(){
       indexer.set_zero_position(indexer.get_position()); 
    }

    void Spin(){
        indexer.move(50);
        
    }
    void Reset(){
        int8_t direction = 1;

            if(indexer.get_position() < 0){
                direction *= -1;
            }
            
            indexer.move(50 * direction);
        while(true){
            std::string thingy = std::to_string((int)indexer.get_position() % 300);
            pros::lcd::set_text(1, thingy);
            
            if((int)indexer.get_position() % 360 > -25 && (int)indexer.get_position() % 300 < 25){
                indexer.move(0);
                indexer.set_brake_mode(MOTOR_BRAKE_HOLD);
                break;
            }
            pros::delay(10);
        }
    }
    void Stop(){
        indexer.move(0);
    }

};