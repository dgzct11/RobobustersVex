#include "main.h"

using namespace pros;
extern int ROLLER_MOTOR_PORT;
class Roller{
    public:
    Motor roller = Motor(ROLLER_MOTOR_PORT);
   
    Roller(){
    }

    void spin(int voltage)
    {
        roller.move(voltage);
    }
    
    void stop()
    {
        roller.move(0);
    }

    void step(){
	roller.move_relative(45,127);
    }
};
