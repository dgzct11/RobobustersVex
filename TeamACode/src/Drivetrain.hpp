#pragma once

#include "Constants.hpp"
#include "Utils.hpp"
#include "main.h"
#include <string>
#include <iostream>

using namespace pros;
using namespace std;
class Drivetrain {
public:
  Motor leftFront = Motor(LEFT_FRONT_PORT, MOTOR_GEARSET_6, true);
  Motor leftBack1 = Motor(LEFT_BACK1_PORT, MOTOR_GEARSET_6);
  Motor leftBack2 = Motor(LEFT_BACK2_PORT, MOTOR_GEARSET_6, true);

  Motor rightFront = Motor(RIGHT_FRONT_PORT, MOTOR_GEARSET_6);
  Motor rightBack1 = Motor(RIGHT_BACK1_PORT, MOTOR_GEARSET_6, true);
  Motor rightBack2 = Motor(RIGHT_BACK2_PORT, MOTOR_GEARSET_6);

  Motor_Group left = Motor_Group({leftFront, leftBack1, leftBack2});
  Motor_Group right = Motor_Group({rightFront, rightBack1, rightBack2});
  Drive driveType;
  Vector2 pos = Vector2(0.0, 0.0);

  Drivetrain(Drive *driveType = new Drive(tank)) {
    this->driveType = *driveType;
  }

  void move(double velocity) {
    left.move(velocity);
    right.move(velocity);
  }
  void PIDMove(double distance) {
    left.tare_position();
    right.tare_position();
    
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
      left.move_voltage(speed * kT * (AverageValueEncoder/AverageLeft));
      right.move_voltage(speed * kT * (AverageValueEncoder/AverageRight));
    }
		}

  void stop() {
    left.move(0);
    right.move(0);
  }

  void turn(double velocity) {
    left.move(velocity);
    right.move(-velocity);
  }

  void update(int leftStick, int rightStick) {
    if (driveType == tank) {
      left.move(leftStick);
      right.move(rightStick);
    } else {
      left.move(leftStick + rightStick);
      right.move(leftStick - rightStick);
    }
  }
};
