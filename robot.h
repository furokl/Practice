#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "enum_states.h"
#include "camera.h"

class Robot
{
private:
	bool power{};

	double	
		x{}, y{}, azimuth{},
		detect_x{}, detect_y{};

	Robot_State state{};

	sf::Texture robot_texture;
	sf::Sprite robot_sprite;

public:
	Robot(double, double);
	void rotate();
	void move(Camera&);
	void take_object();
	void take_out_object();
	void set_state(Robot_State);
	const std::string get_state();

	// SFML

	void draw_robot(sf::RenderWindow&);
};

#endif // !ROBOT_H

