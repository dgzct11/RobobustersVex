#include "main.h"

using namespace pros;

class Catapult{
	private:
	const int ticksTillShot = 100;

	public:

	Motor_Group catapult;

	Catapult(Motor_Group Catapult) : catapult(Catapult){}

	void Cycle(){
		Motor_Group.move_relative(ticksTillShot);
	}
};
