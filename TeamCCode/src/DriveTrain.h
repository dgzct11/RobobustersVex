#pragma once
#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
using namespace pros;

class DriveTrain{
    public:
    Motor leftBack = Motor( LEFT_BACK_PORT);
    Motor leftFront = Motor(LEFT_FRONT_PORT);
    Motor rightBack = Motor(RIGHT_BACK_PORT);
    Motor rightFront = Motor(RIGHT_FRONT_PORT);
    Motor_Group leftMotor = Motor_Group({leftFront, leftBack});
    Motor_Group rightMotor = Motor_Group({rightFront, rightBack});

    DriveTrain(){
        leftMotor.set_reversed(true);
        leftMotor.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        rightMotor.set_brake_modes(E_MOTOR_BRAKE_HOLD);

    }
    void tankDrive(int leftY, int rightY){
        leftMotor.move( leftY);  
        rightMotor.move( rightY);
        
    }
    void arcadeDrive(int leftY, int rightX){
        leftMotor.move(leftY + rightX);
        rightMotor.move(leftY - rightX);
    }
    
    bool overThreshhold(int value)
    {
        return (abs(value)>=1);
    
    }
    void PIDMove(float distance) {
    float ValueLeft = left.get_positions()[0];
    float ValueRight = right.get_positions()[0];
    float AverageValueEncoder;

    float integral;
    float derivative;

    float error;
    float prevError;
    float speed;

    while (fabs(error) > 0.1) {
      AverageValueEncoder = (((float)left.get_positions()[0]) - ValueLeft) +
                            ((float)right.get_positions()[0] - ValueRight) / 2;

      error = distance - AverageValueEncoder;
      integral += error;

                        while(left_pos <= ticks && right_pos <= ticks){
                                if(left_pos > right_pos){
                                        left.move(velocity - 20);
                                        right.move(velocity + 20);
                                }else if(left_pos < right_pos){
                                        left.move(velocity + 20);
                                        right.move(velocity - 20);
                                }else{
                                        left.move(velocity);
                                        right.move(velocity);
                                }
                        }
                }
}; 