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
	//static size_t temp{};
	camera_texture.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\camera.png");
	camera_sprite.setTexture(camera_texture);

	detect_buffer.loadFromFile("C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\cam.ogg");
	detect_sound.setBuffer(detect_buffer);
}

Camera::~Camera() 
{
}

void Camera::rotate() {
	angle += control_system::camera_rotate;
	
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

	if (angle >= 360.f)
		angle = 0.f;
}

void Camera::make_beam(std::vector <Item> &item) {
	float temp_x{ x }, temp_y{ y };

	for (size_t i{}; i < control_system::beam_range; i++)
	{
		temp_x += sin(angle) * control_system::beam_step;
		temp_y += cos(angle) * control_system::beam_step;

		for (size_t j{}; j < item.size(); j++)
		{
			if (((gap.x_min[j] <= temp_x) && (temp_x <= gap.x_max[j]))
				&& ((gap.y_min[j] <= temp_y) && (temp_y <= gap.y_max[j])))
			{
				if (check_item(item[j]))
				{
					state = Camera_State::DETECTED;
					detect = true;
					detect_x = temp_x;
					detect_y = temp_y;
					detect_i = j;
					detect_sound.play();

					item[j].set_item_type();
				}
				break;
			}
		}
	}
	detect_x = temp_x;
	detect_y = temp_y;
	temp_x = 0.f;
	temp_y = 0.f;
}

bool Camera::check_item(Item &item) {
	if (item.get_item_type() == Item_Type::TRASH)
		return true;
	else
		return false;
}

bool Camera::get_detect() {
	return detect;
}

size_t Camera::get_detect_i() {
	return detect_i;
}

void Camera::set_detect_false() {
	detect = false;
}

void Camera::set_detect_coord(float& x_, float& y_) {
	x_ = detect_x;
	y_ = detect_y;
}

void Camera::set_item_points(std::vector<Item> &item) {
	for (size_t i{}; i < item.size(); i++)
	{
		gap.x_min.push_back(item[i].polygon.point[0]);
		gap.y_min.push_back(item[i].polygon.point[1]);
		gap.x_max.push_back(item[i].polygon.point[2]);
		gap.y_max.push_back(item[i].polygon.point[3]);
	}
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

void Camera::draw_beam(sf::RenderWindow &window, std::vector<Item> &item) {
	if (!detect)
	{
		//std::thread th_make_beam(&Camera::make_beam, this, std::ref(item));
		//std::thread th_rotate(&Camera::rotate, this);
		//std::thread th([&] {
			//make_beam(item);
			//rotate();
			//});

		//th.detach();
		make_beam(item);
		rotate();

		//th_make_beam.join();
		//th_rotate.join();
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