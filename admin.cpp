#include "admin.h"

Admin::Admin(std::vector<Robot>& robot, std::vector<Camera>& camera)
{
	for (size_t i{}; i < robot.size(); i++)
	{
		robot_power.push_back(false);
	}
	for (size_t i{}; i < camera.size(); i++)
	{
		camera_power.push_back(false);
	}
}
void Admin::set_robot_on(size_t i) {
	robot_power[i] = true;
}
void Admin::set_camera_on(size_t i) {
	camera_power[i] = true;
}
void Admin::set_robot_off(size_t i) {
	robot_power[i] = false;
}
void Admin::set_camera_off(size_t i) {
	camera_power[i] = false;
}
bool Admin::get_robot_power(size_t i) {
	return robot_power[i];
}
bool Admin::get_camera_power(size_t i) {
	return camera_power[i];
}
void Admin::set_robot_on() {
	for (size_t i{}; i < robot_power.size(); i++)
	{
		robot_power[i] = true;
	}
}
void Admin::set_camera_on() {
	for (size_t i{}; i < camera_power.size(); i++)
	{
		camera_power[i] = true;
	}
}
void Admin::set_robot_off() {
	for (size_t i{}; i < robot_power.size(); i++)
	{
		robot_power[i] = false;
	}
}
void Admin::set_camera_off() {
	for (size_t i{}; i < camera_power.size(); i++)
	{
		camera_power[i] = false;
	}
}
bool Admin::get_robot_power() {
	bool temp{};
	for (size_t i{}; i < robot_power.size(); i++)
	{
		temp = temp || robot_power[i];
	}
	return temp;
}
bool Admin::get_camera_power() {
	bool temp{};
	for (size_t i{}; i < camera_power.size(); i++)
	{
		temp = temp || camera_power[i];
	}
	return temp;
}