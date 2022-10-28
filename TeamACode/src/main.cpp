#include "main.h"
#include "Robot.hpp"
#include "Drivetrain.hpp"
#include <string>
#include <iostream>

using namespace std;

Drive* DriveType = new Drive(split_arcade);

Drivetrain drivetrain(DriveType); 
Roller roller;
Endgame endgame;

Robot robot = Robot(&drivetrain, &roller, &endgame);

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn1_cb(on_center_button);

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	roller.spin(127);
	delay(300);
	drivetrain.move(30);
	delay(250);
	drivetrain.move(0);
	roller.stop();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	Controller master (CONTROLLER_MASTER);
	while (true) {
		drivetrain.update(master.get_analog(ANALOG_LEFT_Y), master.get_analog(ANALOG_RIGHT_X));
		if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
			roller.spin(127);
		}
		else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
			roller.spin(-127);
		}
		else {
			roller.stop();
		}
		if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT) && master.get_digital(E_CONTROLLER_DIGITAL_LEFT) && master.get_digital(E_CONTROLLER_DIGITAL_A)){
			endgame.Shoot();
		}
		drivetrain.odomTick();
		
		/*string position = to_string(drivetrain.pos.x) + " " + to_string(drivetrain.pos.y ) + " " + to_string(drivetrain.theta) + " " + to_string(drivetrain.ifID) + " "  + to_string(drivetrain.publicDeltaLeft) + " " + to_string(drivetrain.publicDeltaRight);

		std::cout << position << std::endl;*/
		pros::delay(10);
	}
}
