#include <iostream>

#include "robot.h"
#include "control_system.h"
#include "math_const.h"

Robot::Robot(double x_, double y_)
	: x(x_), y(y_)
{
	robot_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\robot.png");
	robot_sprite.setTexture(robot_texture);
}

void Robot::rotate() {

}

void Robot::move(Camera& camera) {
	if(camera.get_detect())
	{
		camera.set_detect_coord(detect_x, detect_y);
		double azimuth_rad = atan2(detect_y - y, detect_x - x);
		azimuth = azimuth_rad * 180.0 / math_const::PI;

		bool condition_x = (abs(detect_x - x) > control_system::robot_detect);
		bool condition_y = (abs(detect_y - y) > control_system::robot_detect);

		if (condition_x && condition_y)
		{
			x += cos(azimuth_rad) * control_system::robot_step;
			y += sin(azimuth_rad) * control_system::robot_step;
		}
		else
		{
			camera.set_detect_false();
		}
	}
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

// SFML

void Robot::draw_robot(sf::RenderWindow& window) {
	robot_sprite.setPosition(
		static_cast<float>(x - control_system::robot_displacement),
		static_cast<float>(y - control_system::robot_displacement));
	window.draw(robot_sprite);

}