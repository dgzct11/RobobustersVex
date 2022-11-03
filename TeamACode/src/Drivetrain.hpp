#pragma once

#include "main.h"
#include "Constants.hpp"
#include "Utils.hpp"
#include <string>

using namespace pros;
using namespace std;
class Drivetrain{
	public:
		Motor leftBack = Motor(LEFT_BACK_PORT);
		Motor leftFront = Motor(LEFT_FRONT_PORT);
		Motor rightBack = Motor(RIGHT_BACK_PORT);
		Motor rightFront = Motor(RIGHT_FRONT_PORT);
		Motor_Group left = Motor_Group({leftFront, leftBack});
		Motor_Group right = Motor_Group({rightFront, rightBack});
		Drive driveType;
		Vector2 pos = Vector2(0.0, 0.0);
		double theta;
		double leftEncoder = (leftFront.get_position() + leftBack.get_position()) / 2;
		double rightEncoder = (rightFront.get_position() + rightBack.get_position()) / 2;
		int ifID = -1; 
		double publicDeltaLeft = -1;
		double publicDeltaRight = -1;

		Drivetrain(Drive* driveType = new Drive(tank)){
			this->driveType = *driveType;
			left.set_reversed(true);
			left.set_brake_modes(E_MOTOR_BRAKE_HOLD);
			right.set_brake_modes(E_MOTOR_BRAKE_HOLD);

		}

		bool overThreshhold(double value)
		{

			return (fabs(value)>=1);
		}

		void odomTick(){
			double newLeft = (leftBack.get_position());
			double newRight = (rightBack.get_position());
			double deltaLeft = (newLeft - leftEncoder) * 0.0195; 
			double deltaRight= (newRight - rightEncoder) * 0.0195;
			publicDeltaLeft = deltaLeft;
			publicDeltaRight = deltaRight;
			string position = "deltas: " + to_string(deltaLeft) + " " + to_string(deltaRight) + " " + to_string(pos.x) + " " + to_string(pos.y) + " " + to_string(theta) + " " + to_string(ifID); 
			std::cout << position << std::endl;

			leftEncoder = newLeft;
			rightEncoder = newRight;
			if(deltaLeft == deltaRight){
				pos.y += sin(theta) * deltaLeft;
				pos.x += cos(theta) * deltaRight;
				ifID = 1;
				return;

			}
			else if((deltaLeft > 0 && deltaRight > 0) || (deltaRight < 0 && deltaLeft < 0)){
				double m;
				double R;
				//turn Right
				if(fabs(deltaLeft) < fabs(deltaRight)){
					double temp = deltaLeft;
					deltaLeft = deltaRight;
					deltaRight = temp;
				}
				//turn left
				R = ROBOT_LENGTH / (1 - (deltaRight / deltaLeft));
				m = R - (ROBOT_LENGTH / 2);
				double x1 = cos(theta) * m;
				double y1 = sin(theta) * m;
				theta -= deltaLeft / R;
				double x2 = cos(theta) * m;
				double y2 = sin(theta) * m;
				pos.x += x2 - x1;
				pos.y += y2 - y1;
				ifID = 2;
				return;
			}
			else if(deltaLeft == 0 || deltaRight == 0){
				double dtheta;
				if(deltaLeft > 0){
					dtheta = deltaLeft / ROBOT_LENGTH;

				}
				else{
					dtheta = deltaRight / ROBOT_LENGTH;
				}
				double x1 = cos(theta) * ROBOT_LENGTH;
				double y1 = sin(theta) * ROBOT_LENGTH;
				theta += dtheta;
				double x2 = cos(theta) * ROBOT_LENGTH;
				double y2 = sin(theta) * ROBOT_LENGTH;
				pos.x += x2 - x1;
				pos.y += y2 - y1;
				ifID = 3; 
				return;
			}
			else {
				double m;
				double Rright = ROBOT_LENGTH / (1 + fabs(deltaRight / deltaLeft));
				double Rleft = ROBOT_LENGTH - Rright;
				if(Rright > Rleft){
					double m = Rright - (ROBOT_LENGTH / 2);
				}
				else{
					double m = Rleft - (ROBOT_LENGTH / 2);
				}
				double x1 = cos(theta) * m;
				double y1 = sin(theta) * m;
				theta += Rright / deltaRight;
				double x2 = cos(theta) * m;
				double y2 = sin(theta) * m;
				pos.x += x2 - x1;
				pos.y += y2 - y1;
				ifID = 4;
				return;
			}
			pros::delay(10);
		}

		void move(double velocity){
			left.move(velocity);
			right.move(velocity);
		}

		void turn(double velocity){
			left.move(velocity);
			right.move(-velocity);
		}

		void PIDMove(double distance){
			const double kP;
			const double kI;
			const double kD;

			Vector2 StartingPos = {leftEncoder, rightEncoder};

			double AverageValueEncoder;

			double integral;
			double derivative;

			double error;
			double prevError;
			double speed;

			while(fabs(error) > 0.1){
				AverageValueEncoder = ((leftEncoder - StartingPos.x) + (rightEncoder = StartingPos.y))/2;

				error = distance - AverageValueEncoder;
				integral += error;

				if(error = 0){
					integral = 0;
				}
				if(fabs(error) > 40){
					integral = 0;
				}

				derivative = error - prevError;

				speed = (kP * error) + (kI * integral) + (kD * derivative);

				left.move(speed);
				right.move(speed);
			}
		}

		void PIDTurn(double angle){
			const double kP;
			const double kI;
			const double kD;

			double startingHeading = theta;

			double integral;
			double derivative;

			double error;
			double prevError;
			double speed;

			while(fabs(error) > 0.1){
				error = angle - startingHeading;
				integral += error;

				if(error == 0){
					integral = 0;
				}
				if(fabs(error) > 40){
					integral = 0;
				}

				derivative = error - prevError;

				prevError = error;
				speed = (kP * error) + (kI * integral) + (kD * derivative);

				left.move(speed);
				right.move(-speed);
			}
		}

		void update(int leftStick, int rightStick){
			if(driveType == tank){
				left.move(leftStick);
				right.move(rightStick);
			}else {
				left.move(leftStick + rightStick);
				right.move(leftStick - rightStick);
			}
		}
};
