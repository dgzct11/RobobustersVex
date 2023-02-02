#pragma once

#include <cmath>
namespace Constants {
    static constexpr double pi = 3.14159265359; // pi
    static const double radToDeg = 180/pi;

    static constexpr unsigned char fl_p = 20; // Port of Front Left motor
    static constexpr unsigned char bl_p = 10; // Port of Back Left motor
    static constexpr unsigned char fr_p = 11; // Port of Front Right motor
    static constexpr unsigned char br_p = 1; // Port of Back Right motor

    static constexpr unsigned char intakeL_p = 12; // Port of the Left Intake motor
    static constexpr unsigned char intakeR_p = 2; // Port of the Right Intake motor

    static constexpr unsigned char index_p = 7; // Port of Indexer
    
    static constexpr unsigned char fly_p = 5; // Port of the Flywheel

    static constexpr char xtendL_p = 'A'; // Port of the Left pneumatics system
    static constexpr char xtendR_p = 'B'; // Port of the Right pnewumatics system

    static constexpr unsigned char threshold = 11; // Threshhold for controller to start moving the robot
    
    static constexpr float trackwidth = 9.9f; // The distance between both the left and an right motors

    static constexpr float wheelDiameter = 2.25f; // Diameter of drive wheels
    static constexpr double unitsPerRevolution = 642.8571429; // Motor units per revolution for drive wheels (900 * 5/7)
    static const double inchesPerTick = wheelDiameter*pi/unitsPerRevolution; // The inches per tick for the drive encoders

    static constexpr float maxActVel = 54.0f;
    static const double maxRelVel = maxActVel/inchesPerTick;
    
    static constexpr double accel = 1;
    static constexpr double spacing = 12;

    static inline double headingRestrict(double heading) {
        if (heading <= 0) heading += pi*2;
        heading = fmod(std::abs(heading),pi*2);
        return heading;
    }

    static inline double constrain(double input, double lowerBound, double upperBound) {
        if (input > lowerBound) {
            if (input < upperBound) {
                return input;
            } else {
                return upperBound;
            }
        } else {
            return lowerBound;
        }
    }

    static inline signed char signum(double x){
      return (x > 0) - (x < 0);
    }
};