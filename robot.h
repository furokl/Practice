#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "enum_states.h"
#include "item.h"
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
	sf::SoundBuffer take_buffer;
	sf::SoundBuffer take_out_buffer;
	sf::Sound move_sound;
	sf::Sound rotate_sound;
	sf::Sound take_sound;
	sf::Sound take_out_sound;

public:
	Robot(float, float);
	void calc_azimuth(Camera&);
	void calc_azimuth(Item&);
	void calc_coord(float&, float&);
	void move(Camera&, Item&, Item&);
	void take_object(Item&);
	void take_out_object(Item&, Item&);
	void set_state(Robot_State);
	const std::string get_state();
	void move_robot();
	void turn_right();
	void turn_left();

	// SFML

	void draw_robot(sf::RenderWindow&);
	void play_sound();
};

#endif // !ROBOT_H

