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
	robot_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\robot.png");
	robot_sprite.setTexture(robot_texture);

	move_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\move_mid.ogg");
	move_sound.setBuffer(move_buffer);
	move_sound.setVolume(control_system::sound_master);

	rotate_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\rotate.ogg");
	rotate_sound.setBuffer(rotate_buffer);
	rotate_sound.setVolume(control_system::sound_master);
}

void Robot::rotate() {
	angle += control_system::robot_rotate;
	Sleep(10);
}

void Robot::calc_azimuth(Camera &camera) {
	camera.set_detect_coord(detect_x, detect_y);
	float azimuth_rad = atan2(detect_y - y, detect_x - x);
	azimuth = azimuth_rad * 180.f / math_const::PI;

	if (azimuth < 0)
		azimuth += 360;
	if (azimuth > 360)
		azimuth = 0;
}

void Robot::move(Camera &camera) {
	if(camera.get_detect())
	{
		switch (state)	
		{
		case Robot_State::WAITING:
			if (camera.get_detect())
				state = Robot_State::ROTATED;
			break;

		case Robot_State::ROTATED:
			calc_azimuth(camera);
			turn_robot();
			if (static_cast<int>(angle) == static_cast<int>(azimuth))
				state = Robot_State::MOVING_TO_TRASH;
			break;

		case Robot_State::MOVING_TO_TRASH:
			if ((abs(detect_x - x) > control_system::robot_detect)
				&& (abs(detect_y - y) > control_system::robot_detect))
			{
				move_robot();
				x += cos(azimuth / 180.f * math_const::PI) * control_system::robot_step;
				y += sin(azimuth / 180.f * math_const::PI) * control_system::robot_step;
			}
			else
			{
				camera.set_detect_false();
				state = Robot_State::TAKE_TRASH;
			}
			break;
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

void Robot::move_robot() {
	rotate_x += cos(azimuth / 180.f * math_const::PI) * control_system::robot_step;
	rotate_y += sin(azimuth / 180.f * math_const::PI) * control_system::robot_step;
}

void Robot::turn_robot() {
	rotate();

	float
		x0{ x - control_system::robot_displacement },
		y0{ y - control_system::robot_displacement },
		angle_rad = math_const::PI / 180.f;

	rotate_x = (rotate_x - x0) * cos(angle_rad) - (rotate_y - y0) * sin(angle_rad) + x0;
	rotate_y = (rotate_x - x0) * sin(angle_rad) + (rotate_y - y0) * cos(angle_rad) + y0;

	robot_sprite.setRotation(angle);
}

// SFML

void Robot::draw_robot(sf::RenderWindow& window) {
	robot_sprite.setPosition(rotate_x, rotate_y);
	robot_sprite.move(
		control_system::robot_displacement,
		control_system::robot_displacement);
	
	// <- del
	sf::CircleShape circle(5.f);
	circle.setFillColor(sf::Color(255, 0, 0, 100));
	circle.setPosition(x, y);
	window.draw(circle);

	window.draw(robot_sprite);
}

void Robot::play_sound() {
	switch (state)
	{
	case Robot_State::WAITING:
		//_sound.stop();
		break;
	case Robot_State::ROTATED:
		//_sound.stop();
		if (!rotate_sound.getStatus())
			rotate_sound.play();
		break;

	case Robot_State::MOVING_TO_TRASH:
		rotate_sound.stop();
		if (!move_sound.getStatus())
			move_sound.play();
		break;

	case Robot_State::TAKE_TRASH:
		move_sound.stop();
		break;

	case Robot_State::MOVING_TO_TRASH_CAN:
		break;

	case Robot_State::TAKE_OUT_TRASH:
		break;
	}
}