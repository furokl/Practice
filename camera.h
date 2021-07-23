#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "item.h"

class Camera
{
private:
	std::string
		file_path{ "C:\\Users\\Даниил\\source\\repos\\RoboTrash_SFML\\redist\\" },
		file_name;
	bool	
		thread_flag{ true },
		detect{};
	float	
		x, 
		y, 
		angle{}, 
		detect_x{},
		detect_y{};
	size_t	
		detect_i;

	struct Gap
	{
		std::vector<float> 
			x_min, y_min, 
			x_max, y_max;
	};
 
	Gap gap{};
	Camera_State state{};

	sf::CircleShape beam_circle;
	sf::Texture camera_texture;
	sf::Sprite camera_sprite;

	sf::SoundBuffer detect_buffer;
	sf::Sound detect_sound;

public:
	Camera(float, float);
	~Camera();
	bool check_item(Item &item);
	void make_beam(std::vector<Item> &item);
	void rotate();
	float get_coord_x();
	float get_coord_y();
	bool get_detect();
	size_t get_detect_i();
	void set_detect_false();
	void set_detect_coord(float&, float&);
	void set_item_points(std::vector<Item>&);
	void set_thread_flag(bool);

	// SFML

	void draw_beam(sf::RenderWindow&, std::vector<Item>&);
	void draw_camera(sf::RenderWindow&);
	void draw_beam_range(sf::RenderWindow&);

};

#endif // !CAMERA_H

