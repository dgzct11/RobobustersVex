#pragma once

#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

using namespace pros;
class Endgame{
	public:
	Motor endgame = Motor(ENDGAME_PORT);
	Motor release = Motor(RELEASE_PORT);
	

	void Shoot(){
		release.move(-127);
		delay(100);
		release.move(0);
		endgame.move(127);
	}
	void Off(){
		endgame.move(0);
		release.move(0);
	}
};
