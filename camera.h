#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

class Camera
{
private:
	bool power{};
	double	x, y, angle{};
	Camera_State state{};
	struct Beam
	{
		std::vector<double> beam_x;
		std::vector<double> beam_y;
	};
	Beam beam;

public:
	Camera(double, double);
	void rotate();
	void draw_beam();
	void make_photo();
	void check_item();
	void get_photo();
	void get_coord(double&, double&);
	const std::string get_state();
};

#endif // !CAMERA_H

