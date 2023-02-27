#pragma once

#include "main.h"
#include "Constants.hpp"
#include "Utils.hpp"
#include <string>

using namespace pros;
using namespace std;
class Drivetrain{
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
		
		Drivetrain(Drive* driveType = new Drive(tank)){
			this->driveType = *driveType;
			
		}
		
		void move(double velocity){
			left.move(velocity);
			right.move(velocity);
		}

		void move_ticks(uint16_t ticks, double velocity){
			double left_pos = (left.get_positions()[0] + left.get_positions()[1]) / 2;
			double right_pos = (right.get_positions()[0] + right.get_positions()[1]) / 2;

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

		void stop(){
			left.move(0);
			right.move(0);
		}

		void turn(double velocity){
			left.move(velocity);
			right.move(-velocity);
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
