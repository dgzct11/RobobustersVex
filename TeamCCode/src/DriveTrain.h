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
     void PIDMove(double distance) {
    leftMotor.tare_position();
    rightMotor.tare_position();
    
    double AverageLeft = 0.0;
    double AverageRight = 0.0;
    double AverageValueEncoder = 0.0;

    double integral = 0.0;
    double derivative = 0.0;

    double error = distance;
    double prevError;
    double speed;
    while (fabs(error) > 0.2) {
      AverageLeft = (left.get_positions()[0] + left.get_positions()[1] + 1.0) / 2;
      AverageRight = (right.get_positions()[0] + right.get_positions()[1] + 1.0) / 2;
      
      AverageValueEncoder = (AverageLeft + AverageRight) / 2;

      error = distance - AverageValueEncoder;
      integral += error;

      if (fabs(error) > 40) {
        integral = 0;
      }

      derivative = error - prevError;

      prevError = error;
      speed = clamp((kP * error) + (kI * integral) + (kD * derivative), -11500.0, 11500.0);

      std::cout << AverageLeft << " " << AverageRight << " " << AverageValueEncoder << " " << speed << std::endl;
      std::cout << (speed * AverageValueEncoder/AverageLeft) << " " << (speed * AverageValueEncoder / AverageRight) << std::endl;
      leftMotor.move_voltage(speed * kT * (AverageValueEncoder/AverageLeft));
      rightMotor.move_voltage(speed * kT * (AverageValueEncoder/AverageRight));
    }
		}
}; 