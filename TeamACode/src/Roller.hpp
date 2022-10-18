#include "main.h"

const int ROLLER_MOTOR_PORT = 5;

using namespace pros;
class Roller{
    public:
    Motor roller = Motor(ROLLER_MOTOR_PORT);
   
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
