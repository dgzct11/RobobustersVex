#pragma once

#include "main.h"
#include "pros/motors.hpp"
#include "Constants.hpp"
#include "pros/rtos.h"

using namespace pros;
class Endgame{
	public:
	Motor endgame = Motor(ENDGAME_PORT);
	

	void Shoot(){
		endgame.move(127);
	}
	void off(){
		endgame.move(0);
	}
};
