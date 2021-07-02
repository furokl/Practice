#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "math_const.h"
#include "item.h"

class Camera
{
private:
	bool power{}, detect{};
	double	x{}, y{}, angle{ 0.0 },
		detect_x{}, detect_y{};
 
	struct Beam
	{
		std::vector<double> beam_x;
		std::vector<double> beam_y;
	};
	struct Gap
	{
		double 
			x_min, y_min, 
			x_max, y_max;
	};

	Beam beam; 
	Gap gap;
	Camera_State state{};

	sf::Texture camera_t;
	sf::Sprite camera_s;

public:
	Camera(double, double);
	void rotate();
	void draw_beam();
	void make_photo();
	void check_item();
	void get_photo();
	void set_detect_coord(double&, double&);
	void set_item_points(Item& item);
	const std::string get_state();
};

#endif // !CAMERA_H

