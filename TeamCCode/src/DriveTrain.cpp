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
        rightMotor.set_reversed(true);
    }
    void tankDrive(int leftY, int rightY){
        leftMotor.move(voltage: leftY);
        rightMotor.move(voltage: rightY);
    }
    void arcadeDrive(int leftx, int rightY){

    }
};