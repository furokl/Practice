#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "enum_states.h"
#include "item.h"
#include "camera.h"

class Robot
{
private:
	std::string
		file_path{ "C:\\Users\\Даниил\\source\\repos\\RoboTrash_SFML\\redist\\" },
		file_name;
	bool
		thread_flag{ true };
	float
		x,
		y,
		detect_x, 
		detect_y,
		rotate_x{ x }, 
		rotate_y{ y },
		angle{},
		azimuth{};
	size_t
		detect_i,
		cam_no;

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
	void calc_coord(float&, float&, float&);
	void move(std::vector<Camera>&, std::vector<Item>&, Item&);
	void take_object(Item&);
	void take_out_object(Item&, Item&);
	void set_state(Robot_State);
	void set_thread_flag(bool);
	float get_coord_x();
	float get_coord_y();
	void turn_right();
	void turn_left();

	// SFML

	void draw_robot(sf::RenderWindow&);
	void play_sound();
};

#endif // !ROBOT_H

