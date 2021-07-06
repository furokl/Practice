#include <iostream>
#include <Windows.h>
// for <Windows.h>
#undef min
#undef max

#include "control_system.h"
#include "math_const.h"

#include "robot.h"

Robot::Robot(float x_, float y_)
	: x(x_), y(y_)
{
	robot_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\robot.png");
	robot_sprite.setTexture(robot_texture);
}

void Robot::rotate() {
	angle += control_system::robot_rotate;
	Sleep(10);
}

void Robot::move(Camera& camera) {
	if(camera.get_detect())
	{
		camera.set_detect_coord(detect_x, detect_y);
		float azimuth_rad = atan2(detect_y - y, detect_x - x);
		azimuth = azimuth_rad * 180.f / math_const::PI;
		if (azimuth < 0)
			azimuth += 360.f;

		std::cout << static_cast<int>(azimuth) << ' ' << static_cast<int>(angle) << std::endl; // del

		if (static_cast<int>(angle) == static_cast<int>(azimuth))
		{
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

		else
		{
			draw_turn_robot();
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
	robot_sprite.setPosition(x, y);
	robot_sprite.move(
		control_system::robot_displacement,
		control_system::robot_displacement);

	window.draw(robot_sprite);
}

void Robot::draw_turn_robot() {
	rotate();
	float
		x0{ 700.f - control_system::robot_displacement},
		y0{ 450.f - control_system::robot_displacement},
		angle_rad = math_const::PI / 180.f;

	x = (x - x0) * cos(angle_rad) - (y - y0) * sin(angle_rad) + x0;
	y = (x - x0) * sin(angle_rad) + (y - y0) * cos(angle_rad) + y0;

	robot_sprite.setRotation(angle);
}