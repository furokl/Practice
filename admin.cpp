#include "admin.h"

void Admin::robot_on() {

}

void Admin::robot_off() {

}

void Admin::camera_on() {

}

void Admin::camera_off() {

}

std::string Admin::get_robot_state(Robot& robot) {
	return robot.get_state();
}

std::string Admin::get_camera_state(Camera& camera) {
	return camera.get_state();
}