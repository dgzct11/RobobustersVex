#pragma once

#include "main.h"
#include "../Constants.hpp"
#include "../Display.hpp"
#include "../systems/DriveTrain.hpp"
#include "Vector2.hpp"
#include "Path.hpp"
#include "pros/rtos.hpp"
#include <cmath>
#include <cstdio>
#include <sys/_intsup.h>

using namespace Constants;
using namespace Display;
using namespace pros;

#define ODOM_DEBUG

class Odometry {
	private:
		DriveTrain* dt;
		lv_obj_t** odometryInfo;
		Vector2 points_initial[4] = {Vector2(0,0), Vector2(0,48), Vector2(-48,48), Vector2(0,0)};
		Path p = Path(points_initial, 4);
		
		double newLeft, newRight;
		double phi;
		double dLeft, dRight, rCenter;
		double hCos, hSin, pCos, pSin;
		double* vel = new double[2];

	public:
		Vector2 pos = {0,0};
		double heading = pi/2;
		double leftEncoder, rightEncoder;

		void odomTick(){
			while(true) {
			newLeft = (dt->fl_mtr.get_position() + dt->bl_mtr.get_position()) / 2 * inchesPerTick;
			newRight = (dt->fr_mtr.get_position() + dt->br_mtr.get_position()) / 2 * inchesPerTick;
			
			dLeft = newLeft - leftEncoder;
			dRight = newRight - rightEncoder;

			phi = (dRight-dLeft)/trackwidth;

			if (phi == 0) {
				pos.x += dLeft*cos(heading);
				pos.y += dLeft*sin(heading);
			} else {
				rCenter = ((dLeft+dRight)/2)/phi;

				hCos = cos(heading); hSin = sin(heading);
				pCos = cos(phi); pSin = sin(phi);

				pos.x += (rCenter)*(-hSin + pSin*hCos + hSin*pCos);
				pos.y += (rCenter)*(hCos - pCos*hCos + hSin*pSin);
			}
			heading+=phi;

			heading = headingRestrict(heading);

			vel = p.findRobotVelocities(pos, heading);

			//std::cout << pos.x << " " << pos.y << " " << heading*radToDeg << " " << phi*radToDeg << std::endl;

			leftEncoder = newLeft;
			rightEncoder = newRight;

#ifdef ODOM_DEBUG
			lv_label_set_text(*odometryInfo, ("Position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") \nTheta: " + std::to_string(heading*radToDeg)).c_str());
#endif
			delay(10);
			}
		};

        Odometry(DriveTrain* dt, lv_obj_t** odometryInfo):dt(dt), odometryInfo(odometryInfo){}
		Task odomTask{std::bind(&Odometry::odomTick, this)};

		inline void loadPath(Vector2* points, unsigned short n) {
/*			unsigned short n = 1;
			FILE* points_read = fopen(path2points, "r");

			if (points_read == NULL)
			{
				printf("File not found.");
				throw "NERD";
			}
			short newlines;
			while( (newlines = fgetc(points_read)) != EOF)
			{if (newlines == 10){n++;}}

			rewind(points_read);
			
			Vector2 points[n];

			for (unsigned short i = 0; i < n; i++) {
				fscanf(points_read, "%lf,%lf ", &points[i].x, &points[i].y);
			}
			fclose(points_read);
*/
			p = Path(points, n);
		}
		void followPath() {
			while (pos.x != p.nPoints[p.n-1].x && pos.y != p.nPoints[p.n-1].y) {
				dt->left_g.move_velocity(vel[0]);
				dt->right_g.move_velocity(vel[1]);
			}
			dt->tankDrive(0,0);
		}
};