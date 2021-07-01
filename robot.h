#ifndef ROBOT_H
#define ROBOT_H

#include <string>

#include "enum_states.h"

class Robot
{
private:
	bool power{};
	double	x, y,
		azimuth{};
	Robot_State state{};

public:
	Robot(double, double);
	void rotate();
	void move();
	void calc_azimuth();
	void take_object();
	void take_out_object();
	void set_state(Robot_State);
	const std::string get_state();
};

#endif // !ROBOT_H

