#pragma once

#include "main.h"

using namespace pros;

const std::uint8_t FLYWHEEL_ONE_PORT = 7;
const std::uint8_t FLYWHEEL_TWO_PORT = 8;

class Flywheel{
	public:
	Motor flywheel1 = Motor(FLYWHEEL_ONE_PORT);
	Motor flywheel2 = Motor(FLYWHEEL_TWO_PORT);
	Motor_Group flywheel = Motor_Group({flywheel1,flywheel2});
	
	void spin(int velocity){
		int flywheelVel = 0;
		while(flywheelVel < velocity * .8){
			flywheelVel = (flywheel.get_actual_velocities()[0] + flywheel.get_actual_velocities()[1]) / 2;
			flywheel.move(127);
		}
		flywheel.move(velocity);
	}
};
