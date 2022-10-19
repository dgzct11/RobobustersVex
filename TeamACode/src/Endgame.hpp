#pragma once

#include "main.h"

using namespace pros;

#define PNEUMATICS_ADI_PORT 'A'

class Endgame{
	public:
	bool endgameState = false;
	ADIDigitalOut pneumatics = ADIDigitalOut(PNEUMATICS_ADI_PORT);

	void Shoot(){
		pneumatics.set_value(!endgameState);
	}
};
