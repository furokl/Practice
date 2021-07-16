#ifndef ADMIN_H
#define ADMIN_H

#include "robot.h"
#include "camera.h"

class Admin
{
	std::vector<bool>
		robot_power,
		camera_power;
public:
	Admin(std::vector<Robot>&, std::vector<Camera>&);

	void set_robot_on(size_t);
	void set_camera_on(size_t);
	void set_robot_off(size_t);
	void set_camera_off(size_t);
	bool get_robot_power(size_t);
	bool get_camera_power(size_t);
	void set_robot_on();
	void set_camera_on();
	void set_robot_off();
	void set_camera_off();
	bool get_robot_power();
	bool get_camera_power();

	void add_item();
	void add_robot();
	void add_camera();
	void delete_item();
	void delete_robot();
	void delete_camera();
	std::string get_robot_state(Robot& robot);
	std::string get_camera_state(Camera& camera);


};

#endif // !ADMIN_H

