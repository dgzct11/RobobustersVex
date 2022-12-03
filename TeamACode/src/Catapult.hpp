#pragma once

#include "main.h"

#define BUMPER_PORT 1

using namespace pros;

class Catapult{
	public:

		ADIDigitalIn bumper (BUMPER_PORT);
		Motor_Group catapult;

		Catapult(Motor_Group Catapult) {
			catapult = Catapult;
		}

		void Cycle(){
			catapult.move(127);

			while(!bumper.get_value()){
				pros::Sleep(10);
			}
			catapult.move(0);
		}
};
