#include "main.h"
#include "pros/motors.hpp"
extern int LEFT_BACK_PORT;
extern int LEFT_FRONT_PORT;
extern int RIGHT_BACK_PORT;
extern int RIGHT_FRONT_PORT;
extern double ROBOT_LENGTH;
using namespace pros;
class Drivetrain{
    
    public:
    Motor leftBack = Motor( LEFT_BACK_PORT);
    Motor leftFront = Motor(LEFT_FRONT_PORT);
    Motor rightBack = Motor(RIGHT_FRONT_PORT);
    Motor rightFront = Motor(RIGHT_BACK_PORT);
    Motor_Group leftMotor = Motor_Group({leftFront, leftBack});
    Motor_Group rightMotor = Motor_Group({rightFront, rightBack});
    double x;
    double y;
    double theta;
    int leftEncoder;
    int rightEncoder;

    Drivetrain(){
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
    void setOdometry()
    {
        leftEncoder = leftFront.get_encoder_units();
        rightEncoder = rightFront.get_encoder_units();
        x = 0;
        y = 0;
        theta = 0;
    }
    void update()
    {
        double newLeft = leftFront.get_encoder_units();
        double newRight = rightFront.get_encoder_units();
        double changeLeft = newLeft - leftEncoder;
        double changeRight = newRight - rightEncoder;
        leftEncoder = newLeft;
        rightEncoder = newRight;
        if(changeLeft == changeRight)
        {
            y += sin(theta) * changeLeft;
            x += cos(theta) * changeRight;
            return;
        }
        else if((changeLeft > 0 && changeRight > 0) || (changeRight < 0 && changeLeft < 0))
        {
            double m;
            double R;
            //turn Right
            if(fabs(changeLeft) < fabs(changeRight))
            {
                double temp = changeLeft;
                changeLeft = changeRight;
                changeRight = temp;
            }
            //turn left
            R = ROBOT_LENGTH / (1 - (changeRight / changeLeft));
            m = R - (ROBOT_LENGTH / 2);
                double x1 = cos(theta) * m;
                double y1 = sin(theta) * m;
                theta -= changeLeft / R;
                double x2 = cos(theta) * m;
                double y2 = sin(theta) * m;
                x += x2 - x1;
                y += y2 - y1;
            return;
        }
        else if(changeLeft == 0 || changeRight == 0)
        {
            double dtheta;
            if(changeLeft > 0)
            {
                dtheta = changeLeft / ROBOT_LENGTH;

            }
            else
            {
                dtheta = changeRight / ROBOT_LENGTH;
            }
            double x1 = cos(theta) * ROBOT_LENGTH;
            double y1 = sin(theta) * ROBOT_LENGTH;
            theta += dtheta;
            double x2 = cos(theta) * ROBOT_LENGTH;
            double y2 = sin(theta) * ROBOT_LENGTH;
            x += x2 - x1;
            y += y2 - y1;
            return;
        }
        else {
            double m;
            double Rright = ROBOT_LENGTH / (1 + fabs(changeRight / changeLeft));
            double Rleft = ROBOT_LENGTH - Rright;
            if(Rright > Rleft)
            {
                double m = Rright - (ROBOT_LENGTH / 2);
            }
            else
            {
                double m = Rleft - (ROBOT_LENGTH / 2);
            }
            double x1 = cos(theta) * m;
            double y1 = sin(theta) * m;
            theta += Rright / changeRight;
            double x2 = cos(theta) * m;
            double y2 = sin(theta) * m;
            x += x2 - x1;
            y += y2 - y1;
            return;
        }
    }

};