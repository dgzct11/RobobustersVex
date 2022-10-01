#include "main.h"
using namespace pros;
class DriveTrain{
    public:
    Motor leftBack;
    Motor leftFront;
    Motor rightBack;
    Motor rightFront;
    DriveTrain(){
        leftBack = Motor(extern LEFT_BACK_PORT);
        leftFront = Motor(extern LEFT_FRONT_PORT);
        rightFront = Motor(extern RIGHT_FRONT_PORT);
        leftBack = Motor(extern RIGHT_BACK_PORT);
    }
}
