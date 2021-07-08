#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "enum_states.h"
#include "camera.h"

class Robot
{
private:
	bool power;

	float
		x, y,
		detect_x, detect_y,
		rotate_x{ x }, rotate_y{ y },
		angle{}, azimuth{};

	Robot_State state{};

	sf::Texture robot_texture;
	sf::Sprite robot_sprite;

	sf::SoundBuffer move_buffer;
	sf::SoundBuffer rotate_buffer;
	sf::Sound move_sound;
	sf::Sound rotate_sound;

public:
	Robot(float, float);
	void rotate();
	void calc_azimuth(Camera&);
	void move(Camera&);
	void take_object();
	void take_out_object();
	void set_state(Robot_State);
	const std::string get_state();
	void move_robot();
	void turn_robot();

	// SFML

	void draw_robot(sf::RenderWindow&);
	void play_sound();
};

#endif // !ROBOT_H

