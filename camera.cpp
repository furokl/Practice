#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

#include "control_system.h"
#include "math_const.h"
#include "enum_states.h"

#include "camera.h"

Camera::Camera(float x_, float y_)
	: x(x_), y(y_)
{
	camera_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\camera.png");
	camera_sprite.setColor(sf::Color(255, 255, 255, 100));
	camera_sprite.setTexture(camera_texture);

	detect_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\cum.ogg");
	detect_sound.setBuffer(detect_buffer);
	detect_sound.setVolume(control_system::sound_master);
}

void Camera::rotate() {
	angle += control_system::camera_rotate;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	if (angle >= 360.f)
		angle = 0.f;
}

void Camera::make_beam(Item &item) {
	float temp_x{ x }, temp_y{ y };
	if (!detect) {
		for (int i{}; i < control_system::beam_range; i++)
		{
			temp_x += sin(angle) * control_system::beam_step;
			temp_y += cos(angle) * control_system::beam_step;

			if (((gap.x_min <= temp_x) && (temp_x <= gap.x_max)) &&
				((gap.y_min <= temp_y) && (temp_y <= gap.y_max)))
			{
				if (check_item(item))
				{
					state = Camera_State::DETECTED;
					detect = true;
					detect_x = temp_x;
					detect_y = temp_y;
					detect_sound.play();
					item.set_item_type();
				}
				break;
			}
		}
		detect_x = temp_x;
		detect_y = temp_y;
		temp_x = 0.f;
		temp_y = 0.f;
	}
}

void Camera::make_photo() {

}

bool Camera::check_item(Item &item) {
	if (item.get_item_type() == Item_Type::TRASH)
		return true;
	else
		return false;
}

void Camera::get_photo() {

}

bool Camera::get_detect() {
	return detect;
}

void Camera::set_detect_false() {
	detect = false;
}

void Camera::set_detect_coord(float& x_, float& y_) {
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
	if (!detect)
	{
		make_beam(item);
		rotate();
	}

	draw_beam_range(window);

	sf::Vertex beam[2] =
	{
		sf::Vertex(sf::Vector2f(x, y)),
		sf::Vertex(sf::Vector2f(detect_x, detect_y)),
	};
	beam[0].color = sf::Color(255, 0, 0, 160);
	beam[1].color = sf::Color(255, 41, 41, 160);

	window.draw(beam, 2, sf::Lines);
}

void Camera::draw_camera(sf::RenderWindow &window) {
	camera_sprite.setPosition(x, y);
	camera_sprite.move(
		control_system::camera_displacement,
		control_system::camera_displacement);

	window.draw(camera_sprite);
}

void Camera::draw_beam_range(sf::RenderWindow& window) {
	beam_circle.setPosition(x, y);
	beam_circle.move(
		control_system::circle_displacement,
		control_system::circle_displacement);

	beam_circle.setPointCount(50);

	beam_circle.setRadius(control_system::beam_circle);
	beam_circle.setFillColor(sf::Color(0, 0, 0, 0));
	beam_circle.setOutlineThickness(2.f);
	beam_circle.setOutlineColor(sf::Color(255, 0, 0, 100));

	window.draw(beam_circle);
}