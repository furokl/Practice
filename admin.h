#ifndef ADMIN_H
#define ADMIN_H

#include "robot.h"
#include "camera.h"

class Admin
{
public:
	void robot_on();
	void robot_off();
	void camera_on();
	void camera_off();
	std::string get_robot_state(Robot& robot);
	std::string get_camera_state(Camera& camera);
};

#endif // !ADMIN_H

