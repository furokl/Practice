#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "math_const.h"
#include "item.h"

class Camera
{
private:
	bool power{}, detect{};
	double	x, y, angle{45.0 };
	Camera_State state{};

	struct Beam
	{
		std::vector<double> beam_x;
		std::vector<double> beam_y;
	};
	Beam beam;

	std::vector<double> gap{ 0.0, 0.0, 0.0, 0.0 }; // xmin ymin xmax ymax

public:
	Camera(double, double);
	void rotate();
	void draw_beam();
	void make_photo();
	void check_item();
	void get_photo();
	void get_coord(double&, double&);
	void set_item_point(Item& item);
	const std::string get_state();
};

#endif // !CAMERA_H

