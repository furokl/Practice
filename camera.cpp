#include <iostream>
#include <cmath>

#include "control_system.h"
#include "math_const.h"
#include "enum_states.h"

#include "camera.h"

Camera::Camera(double x_, double y_)
	: x(x_), y(y_)
{
}

void Camera::rotate() {
	angle += control_system::rotate;
}

void Camera::draw_beam() {
	double temp_x{ x }, temp_y{ y };
	bool condition_x;
	bool condition_y;

	for (int i{}; i < control_system::beam_range; i++)
	{
		beam.beam_x.push_back(temp_x);
		beam.beam_y.push_back(temp_y);
		temp_x += sin(angle) * control_system::beam_step;
		temp_y += cos(angle) * control_system::beam_step;

		((gap[0] < temp_x) && (temp_x < gap[2])) ? 
			condition_x = true : condition_x = false;
		((gap[1] < temp_x) && (temp_x < gap[3])) ? 
			condition_y = true : condition_y = false;

		if (condition_x && condition_y)
		{
			detect = true;
			break;
		}
	}
}

void Camera::make_photo() {

}

void Camera::check_item() {

}

void Camera::get_photo() {

}

void Camera::get_coord(double& x_, double& y_) {
	x_ = x;
	y_ = y;
}

void Camera::set_item_point(Item& item) {
	for (int i{}; i < gap.size(); i++)
	{
		gap[i] = item.polygon.point[i];
	}
}

const std::string Camera::get_state() {
	switch (state)
	{
	case Camera_State::WAITING:
		return "waiting...";

	case Camera_State::MAKE_PHOTO:
		return "make a photo";

	case Camera_State::SEND_PHOTO:
		return "send a photo";

	case Camera_State::ROTATED:
		return "rotated";

	default:
		std::cout << "\n!!!\tDefault case print_camera_state()" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}