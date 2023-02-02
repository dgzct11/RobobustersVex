#include "main.h"
#include "pros/rtos.h"
#include "systems/DriveTrain.hpp"
#include "systems/Indexer.hpp"
#include "systems/Extender.hpp"
#include "systems/Flywheel.hpp"
#include "systems/Intake.hpp"
#include "autonomous/Odometry.hpp"
#include <sys/_intsup.h>


using namespace pros;
using namespace Display;

Controller master(E_CONTROLLER_MASTER);

DriveTrain dt = DriveTrain();
Flywheel fly = Flywheel();
Intake intk = Intake();
Indexer indx = Indexer();
Extender xtend = Extender();

LV_IMG_DECLARE(normal);
lv_obj_t* backgroundImage = lv_img_disp(&normal);

lv_obj_t * odometryInfo = createLabel(lv_scr_act(), 150, 90, 150, 40, "Odom Info");
Odometry odom = Odometry(&dt, &odometryInfo);

bool arcade;

inline lv_res_t toggleMode(lv_obj_t * btn)
{
    if (arcade) {
	dt.teleMove = [=]{dt.tankDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));};
    } else {
	dt.teleMove = [=]{dt.arcadeDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));};
    }
	arcade = !arcade;

	btnSetToggled(btn, arcade);

    return LV_RES_OK;
}

bool rightSide;

inline lv_res_t toggleSide(lv_obj_t * btn) {
	rightSide = !rightSide;

	btnSetToggled(btn, rightSide);

	return LV_RES_OK;
}

void initialize() {

	lv_obj_t* modeButton = createBtn(lv_scr_act(),  200,  10, 150,  20, "Toggle Mode");
	lv_style_t* modeBtnSty = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(0, 100, 0), LV_COLOR_MAKE(0, 125, 0), LV_COLOR_MAKE(0, 150, 150), LV_COLOR_MAKE(0, 150, 175), LV_COLOR_MAKE(255, 255, 255));
	setBtnStyle(modeBtnSty, modeButton);
	lv_btn_set_action(modeButton, LV_BTN_ACTION_CLICK, toggleMode);

	lv_obj_t* teamButton = createBtn(lv_scr_act(), 200, 50,  150,  20, "Toggle Side");
	lv_style_t* teamBtnSty = createBtnStyle(&lv_style_plain, LV_COLOR_MAKE(0, 0, 255), LV_COLOR_MAKE(0, 0, 125), LV_COLOR_MAKE(255, 0, 0), LV_COLOR_MAKE(125, 0, 0), LV_COLOR_MAKE(255, 255, 255));
	setBtnStyle(teamBtnSty, teamButton);
	lv_btn_set_action(teamButton, LV_BTN_ACTION_CLICK, toggleSide);

	//lv_style_t* textSty = createLabelSty(&lv_style_plain, LV_COLOR_MAKE(0,0,0), LV_COLOR_MAKE(255,255,255), LV_OPA_50);
	//lv_label_set_style(odometryInfo, &textSty[0]);

	dt.teleMove = [=]{dt.tankDrive(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y),master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));};
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
	//odom.loadPath("/usd/points.dat", "/usd/distances.dat");
	//odom.followPath();
	if (rightSide) {
		odom.followPath();
		delay(1000);
	} else {
		dt.tankDrive(-69, -69);
		delay(1000);
		dt.tankDrive(0, 0);
	}
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
	unsigned int startTime = millis();
	unsigned int xChangeTime;
	unsigned int nChangeTime;
	bool xChange = false;
	bool nChange = false;
	while (true) {
		dt.teleMove();

		if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {intk.move(127);}
		else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {intk.move(-127);}
		else {intk.move(0);}

		if (master.get_digital(E_CONTROLLER_DIGITAL_UP)) {fly.move(127);}
		else if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {fly.move(0);}

		if (master.get_digital(E_CONTROLLER_DIGITAL_X)) {indx.launch(); nChange=true; nChangeTime=millis();}
		else if (nChange && millis()-nChangeTime >= 500) {indx.reset(); nChange=false;}

		if(millis()-startTime >= 90000){
			if (master.get_digital(E_CONTROLLER_DIGITAL_A)) {xtend.set(true); xChange=true; xChangeTime=millis();}
			else if (xChange && millis()-xChangeTime >= 500) {xtend.set(false); xChange=false;}
		}
		
        delay(20);
    }
}