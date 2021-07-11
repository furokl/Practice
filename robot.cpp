#include <iostream>
#include <thread>
#include <chrono>
//#include <boost/thread/thread.hpp>

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

	take_out_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\take_out.ogg");
	take_out_sound.setBuffer(take_out_buffer);
	take_out_sound.setVolume(control_system::sound_master);

	take_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\take.ogg");
	take_sound.setBuffer(take_buffer);
	take_sound.setVolume(control_system::sound_master);

}

void Robot::calc_azimuth(Camera &camera) {
	camera.set_detect_coord(detect_x, detect_y);
	float azimuth_rad = atan2(detect_y - y, detect_x - x);
	azimuth = azimuth_rad * 180.f / math_const::PI;
}

void Robot::calc_azimuth(Item& trash_can) {
	float azimuth_rad = atan2(
		trash_can.get_coord_y() - y,
		trash_can.get_coord_x() - x);
	azimuth = azimuth_rad * 180.f / math_const::PI;
}

void Robot::calc_coord(float &x_, float &y_) {
	x_ += cos(azimuth / 180.f * math_const::PI) * control_system::robot_step;
	y_ += sin(azimuth / 180.f * math_const::PI) * control_system::robot_step;
}

void Robot::move(Camera &camera, Item &item, Item &trash_can) {
	switch (state)
	{
	case Robot_State::WAITING:
		if (camera.get_detect())
		{
			state = Robot_State::ROTATED;
		}
		break;

	case Robot_State::ROTATED:
		calc_azimuth(camera);
		((azimuth - angle) < 0) ? turn_right() : turn_left();

		if (static_cast<int>(angle) == static_cast<int>(azimuth))
		{
			state = Robot_State::MOVING_TO_TRASH;
		}
		break;

	case Robot_State::MOVING_TO_TRASH:
		calc_coord(rotate_x, rotate_y);
		calc_coord(x, y);

		if (((abs(detect_x - x)) < control_system::robot_detect)
			&& ((abs(detect_y - y)) < control_system::robot_detect))
		{
			camera.set_detect_false();
			state = Robot_State::TAKE_TRASH;
		}
		break;

	case Robot_State::TAKE_TRASH:
		take_object(item);

		if ((abs((item.get_coord_x() - x) / control_system::robot_throw) < 0.1f)
			&& (abs((item.get_coord_y() - y) / control_system::robot_throw) < 0.1f))
		{
			state = Robot_State::ROTATED_TO_TRASH_CAN;
		}
		break;

	case Robot_State::ROTATED_TO_TRASH_CAN:
		calc_azimuth(trash_can);
		((azimuth - angle) < 0) ? turn_right() : turn_left();

		if (static_cast<int>(angle) == static_cast<int>(azimuth))
		{
			state = Robot_State::MOVING_TO_TRASH_CAN;
		}
		break;

	case Robot_State::MOVING_TO_TRASH_CAN:
		calc_coord(rotate_x, rotate_y);
		calc_coord(x, y);
		item.set_coord(x, y);

		if ((abs(trash_can.get_coord_x() - x) < control_system::robot_detect)
			&& (abs(trash_can.get_coord_y() - y) < control_system::robot_detect))
		{
			state = Robot_State::TAKE_OUT_TRASH;
		}
		break;

	case Robot_State::TAKE_OUT_TRASH:
		take_out_object(item, trash_can);

		if ((abs((item.get_coord_x() - trash_can.get_coord_x()) 
				/ control_system::robot_throw) < 0.1f)
			&& (abs((item.get_coord_y() - trash_can.get_coord_y()) 
				/ control_system::robot_throw) < 0.1f))
		{
			state = Robot_State::WAITING;
		}
		break;
	}
}

void Robot::take_object(Item &item) {
	float
		temp_x{ item.get_coord_x() },
		temp_y{ item.get_coord_y() };

	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	temp_x += (x - item.get_coord_x()) / control_system::robot_throw;
	temp_y += (y - item.get_coord_y()) / control_system::robot_throw;

	item.set_coord(temp_x, temp_y);
}

void Robot::take_out_object(Item &item, Item &trash_can) {
	float
		temp_x{ item.get_coord_x() },
		temp_y{ item.get_coord_y() };

	std::this_thread::sleep_for(std::chrono::milliseconds(5));

	temp_x += (trash_can.get_coord_x() - item.get_coord_x())
		/ control_system::robot_throw;
	temp_y += (trash_can.get_coord_y() - item.get_coord_y()) 
		/ control_system::robot_throw;

	item.set_coord(temp_x, temp_y);
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

void Robot::turn_right() {
	angle -= control_system::robot_rotate;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	float
		x0{ x - control_system::robot_displacement },
		y0{ y - control_system::robot_displacement },
		angle_rad = -math_const::PI / 180.f;

	rotate_x = (rotate_x - x0) * cos(angle_rad) - (rotate_y - y0) * sin(angle_rad) + x0;
	rotate_y = (rotate_x - x0) * sin(angle_rad) + (rotate_y - y0) * cos(angle_rad) + y0;

	robot_sprite.setRotation(angle);
}

void Robot::turn_left() {
	angle += control_system::robot_rotate;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

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
		if (!take_sound.getStatus())
			take_sound.play();
		break;

	case Robot_State::ROTATED_TO_TRASH_CAN:
		move_sound.stop();
		if (!rotate_sound.getStatus())
			rotate_sound.play();
		break;

	case Robot_State::MOVING_TO_TRASH_CAN:
		rotate_sound.stop();
		if (!move_sound.getStatus())
			move_sound.play();
		break;

	case Robot_State::TAKE_OUT_TRASH:
		move_sound.stop();
		if (!take_out_sound.getStatus())
			take_out_sound.play();
		break;
	}
}