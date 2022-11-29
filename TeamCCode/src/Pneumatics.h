#include "main.h"
#include "Constants.hpp"
#include "pros/adi.hpp"
using namespace pros;

class Pneumatics{
    public: 
    ADIDigitalOut pneumatics = ADIDigitalOut(PNEUMATICS_PORT);

    void setValue(bool value){
        pneumatics.set_value(value);
    }
};