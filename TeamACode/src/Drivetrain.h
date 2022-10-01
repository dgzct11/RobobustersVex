#include "main.h"
#include "pros/motors.hpp"
extern int LEFT_BACK_PORT;
extern int LEFT_FRONT_PORT;
extern int RIGHT_BACK_PORT;
extern int RIGHT_FRONT_PORT;
using namespace pros;
class DriveTrain{
    public:
    Motor leftBack = Motor( LEFT_BACK_PORT);
    Motor leftFront = Motor(LEFT_FRONT_PORT);
    Motor rightBack = Motor(RIGHT_FRONT_PORT);
    Motor rightFront = Motor(RIGHT_BACK_PORT);
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
        if(!overThreshhold(leftY))
        {
            leftMotor.move_velocity(0);
        }
        if(!overThreshhold(rightY))
        {
           rightMotor.move_velocity(0);
        }
    }
    void arcadeDrive(int leftY, int rightX){
        leftMotor.move(leftY + rightX);
        rightMotor.move(leftY - rightX);
    }
    
    bool overThreshhold(int value)
    {
        
        return (abs(value)>=1);
    }
};