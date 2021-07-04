#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "item.h"

class Camera
{
private:
	bool power{}, detect{};
	double	x{}, y{}, angle{ 0.0 },
		detect_x{}, detect_y{};

	struct Gap
	{
		double 
			x_min, y_min, 
			x_max, y_max;
	};
 
	Gap gap;
	Camera_State state{};

	sf::Texture camera_texture;
	sf::Sprite camera_sprite;

public:
	Camera(double, double);
	void rotate();
	void make_beam(Item&);
	void make_photo();
	void check_item();
	void get_photo();
	void set_detect_coord(double&, double&);
	void set_item_points(Item& item);
	const std::string get_state();

	// SFML

	void draw_beam(sf::RenderWindow&, Item&);
	void draw_camera(sf::RenderWindow&);
};

#endif // !CAMERA_H

