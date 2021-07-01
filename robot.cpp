#include <iostream>

#include "robot.h"

Robot::Robot(double x_, double y_)
	: x(x_), y(y_)
{
}

void Robot::rotate() {

}

void Robot::move() {

}

void Robot::calc_azimuth() {

}

void Robot::take_object() {

}

void Robot::take_out_object() {

}

void Robot::set_state(Robot_State state_) {
	state = state_;
}

const std::string Robot::get_state() {
	switch (state)
	{
	case Robot_State::WAITING:
		return "waiting...";

	case Robot_State::MOVING_TO_TRASH:
		return "moving to trash";

	case Robot_State::MOVING_TO_TRASH_CAN:
		return "moving to trash can";

	case Robot_State::TAKE_TRASH:
		return "take the trash";

	case Robot_State::TAKE_OUT_TRASH:
		return "take out the trash";

	case Robot_State::ROTATED:
		return "rotated";

	default:
		std::cout << "\n!!!\tDefault case print_robot_state()" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}