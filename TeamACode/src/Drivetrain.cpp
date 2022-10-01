#include "main.h"
#include "pros/motors.h"
#include "pros/motors.hpp"

extern int FRONT_LEFT_MOTOR_PORT;
extern int FRONT_RIGHT_MOTOR_PORT;
extern int BACK_LEFT_MOTOR_PORT;
extern int BACK_RIGHT_MOTOR_PORT;

using namespace pros;

class Drivetrain{
    public:
    Motor leftFront = Motor(FRONT_LEFT_MOTOR_PORT);
    Motor rightFront = Motor(FRONT_RIGHT_MOTOR_PORT);
    Motor leftBack = Motor(BACK_LEFT_MOTOR_PORT);
    Motor rightBack = Motor(BACK_RIGHT_MOTOR_PORT);
   
    Motor_Group leftMotor = Motor_Group({leftFront, leftBack});;
    Motor_Group rightMotor = Motor_Group({leftFront, rightFront});
    Drivetrain(){
        rightMotor.set_reversed(true);
    }

    void tankDrive(int leftY, int rightY)
    {
        leftMotor.move(leftY);
        rightMotor.move(rightY);
    }

    void arcadeDrive(int leftY, int rightX)
    {
        leftMotor.move(leftY + rightX);
        rightMotor.move(leftY - rightX);
    }






};