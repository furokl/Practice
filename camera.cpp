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

	for (int i{}; i < control_system::beam_range; i++)
	{
		beam.beam_x.push_back(temp_x);
		beam.beam_y.push_back(temp_y);
		temp_x += sin(angle) * control_system::beam_step;
		temp_y += cos(angle) * control_system::beam_step;
	}

	//	del
	std::cout << "\n\tXXXX" << std::endl;
	for (const auto& i : beam.beam_x)
		std::cout << i << '\t';
	std::cout << "\n\tYYYY" << std::endl;
	for (const auto& i : beam.beam_y)
		std::cout << i << '\t';
	std::cout << "\n\tsin(" << angle << ") = " << sin(angle);
	std::cout << "\n\tcos(" << angle << ") = " << cos(angle);
	// <- del
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