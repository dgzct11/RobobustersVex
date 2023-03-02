#pragma once

#include "Constants.hpp"
#include "main.h"

using namespace pros;

class Catapult {
public:
  Motor catapult = Motor(CATA_MOTOR_PORT, true);
  ADIDigitalIn button = ADIDigitalIn('A');

  void Shoot() {
    catapult.set_brake_mode(E_MOTOR_BRAKE_COAST);
    catapult.move(127);

    while (!button.get_value()) {
      pros::delay(10);
    }
    pros::delay(50);
    catapult.move(0);
    catapult.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  }
};
