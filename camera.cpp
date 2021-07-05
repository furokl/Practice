#include <iostream>
#include <cmath>
#include <Windows.h>
// for <Windows.h>
#undef min
#undef max

#include "control_system.h"
#include "math_const.h"
#include "enum_states.h"

#include "camera.h"

Camera::Camera(double x_, double y_)
	: x(x_), y(y_)
{
	camera_texture.loadFromFile("D:\\FuroK\\Visual Studio\\Texture\\Practice\\camera.png");
	camera_sprite.setTexture(camera_texture);
}

void Camera::rotate() {
	angle += control_system::camera_rotate;
	Sleep(50);

	if (angle >= 360.0)
		angle = 0.0;
	
}

void Camera::make_beam(Item &item) {
	double temp_x{ x }, temp_y{ y };
	bool condition_x;
	bool condition_y;

	if (!detect) {
		for (int i{}; i < control_system::beam_range; i++)
		{
			temp_x += sin(angle) * control_system::beam_step;
			temp_y += cos(angle) * control_system::beam_step;

			((gap.x_min <= temp_x) && (temp_x <= gap.x_max)) ?
				condition_x = true : condition_x = false;
			((gap.y_min <= temp_y) && (temp_y <= gap.y_max)) ?
				condition_y = true : condition_y = false;

			if ((condition_x) && (condition_y) && (item.get_item_type()))
			{
				state = Camera_State::DETECTED;
				detect = true;
				detect_x = temp_x;
				detect_y = temp_y;

				break;
			}
		}
		detect_x = temp_x;
		detect_y = temp_y;
		temp_x = 0.0;
		temp_y = 0.0;
	}
}

void Camera::make_photo() {

}

void Camera::check_item() {

}

void Camera::get_photo() {

}

bool Camera::get_detect() {
	return detect;
}

void Camera::set_detect_false() {
	detect = false;
}

void Camera::set_detect_coord(double& x_, double& y_) {
	x_ = detect_x;
	y_ = detect_y;
}

void Camera::set_item_points(Item& item) {
	gap.x_min = item.polygon.point[0];
	gap.y_min = item.polygon.point[1];
	gap.x_max = item.polygon.point[2];
	gap.y_max = item.polygon.point[3];
}

const std::string Camera::get_state() {
	switch (state)
	{
	case Camera_State::WAITING:
		return "waiting...";

	case Camera_State::DETECTED:
		return "detected!";

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

// SFML

void Camera::draw_beam(sf::RenderWindow &window, Item &item) {
	sf::Vertex beam[2] =
	{
		sf::Vertex(sf::Vector2f(
			static_cast<float>(x + control_system::camera_displacement),
			static_cast<float>(y + control_system::camera_displacement))),
		sf::Vertex(sf::Vector2f(
			static_cast<float>(detect_x),
			static_cast<float>(detect_y))),
	};

	beam[0].color = sf::Color(255, 0, 0, 160);
	beam[1].color = sf::Color(255, 41, 41, 160);

	window.draw(beam, 2, sf::Lines);
	if (!detect)
	{
		make_beam(item);
		rotate();
	}
}

void Camera::draw_camera(sf::RenderWindow &window) {
	camera_sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
	window.draw(camera_sprite);
}