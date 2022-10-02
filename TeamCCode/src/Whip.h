#include "main.h"
using namespace pros;
extern int WHIP_PORT, WHIP_VOLTAGE;
class Whip{
    public:
    Motor whipMotor = Motor(WHIP_PORT);
    Whip(){
        whipMotor.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    }
    void whip()
    {
        whipMotor.move(WHIP_VOLTAGE);
    }
    void noWhip()
    {
        whipMotor.move(0);
    }
};
