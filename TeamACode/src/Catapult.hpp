#pragma once

#include "main.h"

using namespace pros;

class Catapult{
	public:

		Motor_Group catapult;

		Catapult(Motor_Group Catapult) {
			catapult = Catapult;
		}
};
