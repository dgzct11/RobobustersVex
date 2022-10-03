#include "main.h"
#include "utils.cpp"
extern int LEFT_BACK_PORT;
extern int LEFT_FRONT_PORT;
extern int RIGHT_BACK_PORT;
extern int RIGHT_FRONT_PORT;
extern double ROBOT_LENGTH;
using namespace pros;
class Drivetrain{
    
    public:
    Motor leftBack = Motor( LEFT_BACK_PORT);
    Motor leftFront = Motor(LEFT_FRONT_PORT);
    Motor rightBack = Motor(RIGHT_FRONT_PORT);
    Motor rightFront = Motor(RIGHT_BACK_PORT);
    Motor_Group left = Motor_Group({leftFront, leftBack});
    Motor_Group right = Motor_Group({rightFront, rightBack});
    Drive drivetrain;
    double x;
    double y;
    double theta;

    double leftEncoder = left.get_positions();
    double rightEncoder = right.get_positions();

    Drivetrain(Drive drivetrain) : drivetrain(drivetrain){
        left.set_reversed(true);
        left.set_brake_modes(E_MOTOR_BRAKE_HOLD);
        right.set_brake_modes(E_MOTOR_BRAKE_HOLD);

    }
    
    bool overThreshhold(double value)
    {
        
        return (fabs(value)>=1);
    }

    void odomTick()
    {
        double newLeft = left.get_encoder_units();
        double newRight = right.get_encoder_units();
        double deltaLeft = newLeft - leftEncoder;
        double deltaRight= newRight - rightEncoder;
        leftEncoder = newLeft;
        rightEncoder = newRight;
        if(deltaLeft == deltaRight)
        {
            y += sin(theta) * deltaLeft;
            x += cos(theta) * deltaRight;
            return;
        }
        else if((deltaLeft > 0 && deltaRight > 0) || (deltaRight < 0 && deltaLeft < 0))
        {
            double m;
            double R;
            //turn Right
            if(fabs(deltaLeft) < fabs(deltaRight))
            {
                double temp = deltaLeft;
                deltaLeft = deltaRight;
                deltaRight = temp;
            }
            //turn left
            R = ROBOT_LENGTH / (1 - (deltaRight / deltaLeft));
            m = R - (ROBOT_LENGTH / 2);
                double x1 = cos(theta) * m;
                double y1 = sin(theta) * m;
                theta -= deltaLeft / R;
                double x2 = cos(theta) * m;
                double y2 = sin(theta) * m;
                x += x2 - x1;
                y += y2 - y1;
            return;
        }
        else if(deltaLeft == 0 || deltaRight == 0)
        {
            double dtheta;
            if(changeLeft > 0)
            {
                dtheta = deltaLeft / ROBOT_LENGTH;

            }
            else
            {
                dtheta = deltaRight / ROBOT_LENGTH;
            }
            double x1 = cos(theta) * ROBOT_LENGTH;
            double y1 = sin(theta) * ROBOT_LENGTH;
            theta += dtheta;
            double x2 = cos(theta) * ROBOT_LENGTH;
            double y2 = sin(theta) * ROBOT_LENGTH;
            x += x2 - x1;
            y += y2 - y1;
            return;
        }
        else {
            double m;
            double Rright = ROBOT_LENGTH / (1 + fabs(deltaRight / deltaLeft));
            double Rleft = ROBOT_LENGTH - Rright;
            if(Rright > Rleft)
            {
                double m = Rright - (ROBOT_LENGTH / 2);
            }
            else
            {
                double m = Rleft - (ROBOT_LENGTH / 2);
            }
            double x1 = cos(theta) * m;
            double y1 = sin(theta) * m;
            theta += Rright / deltaRight;
            double x2 = cos(theta) * m;
            double y2 = sin(theta) * m;
            x += x2 - x1;
            y += y2 - y1;
            return;
        }
    }

    void move(double velocity){
	left.move(velocity;
	right.move(velocity);
    }

    void turn(double velocity){
	left.move(velocity);
	right.move(-velocity);
    }

    void update(int leftStick, int rightStick){
	if(drivetrain == Drivetrain.tank){
	left.move(leftStick);
	right.move(rightStick);
	}else if(drivetrain == Drivetrain.split_arcade){
	left.move(leftStick + rightStick);
	right.move(leftStick - rightStick);
	}
    }

};
