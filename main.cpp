/*	*****************************************************************
	Практика 2-го курса студентов МАИ

	Задание '4'		"Программа для роя роботов, которые убирают мусор 
					 в заданное место в комнате"

	Выполнили:		Логунов Д.С. 
					Смыслов И.В. 
					Шемяков В.О.	(гр. М3О-214Б-19)

	Проверил:		Максимов А.Н.
	*****************************************************************/	

#include <iostream>
#include <cmath>
#include <vector>

#include "enum_states.h"
#include "math_const.h"

class Item
{
private:
	double x, y;
	Item_Type type{};
	// add length + enum figure_type + (struct points?)
public:
	Item(double x_, double y_, Item_Type type_)
		: x(x_), y(y_), type(type_)
	{
	}

	void get_item_coord(double &temp_x, double &temp_y) {
		temp_x = x;
		temp_y = y;
	}

	bool get_item_type() {
		switch (type)
		{
		case Item_Type::TRASH:
				return true;

		case Item_Type::NOT_TRASH:
				return false;

		default:
			std::cout << "\n!!!\tDefault case get_item_type()" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
};

class Camera 
{
public:
	struct Beam
	{
		std::vector<double> beam_x;
		std::vector<double> beam_y;
	};
private:
	bool power{};
	double	x, y,
			angle{45.0};
	Camera_State state{};

	
	Beam beam;

public:
	Camera(double x_, double y_)
		: x(x_), y(y_)
	{
	}

	void rotate() {
		angle += 0.5;

	}

	void print_beam() {
		// y = k*x + b
		double k = tan(angle * math_const::PI / 180.0); // add tan 0 tan 90
		double b = y - k * x;

		double temp_x{ x }, temp_y{ y };
		double dx{ 0.5 };
		//	del
		std::cout << std::endl;
		// <-
		for (int i{}; i < 100; i++) 
		{
			beam.beam_x.push_back(temp_x);
			beam.beam_y.push_back(temp_y);
			temp_x += dx;
			temp_y = k * temp_x + b;		
		}
		//	del
		std::cout << "\n\tXXXX" << std::endl;
		for (const auto& i : beam.beam_x)
			std::cout << i << '\t';
		std::cout << "\n\tYYYY" << std::endl;
		for (const auto& i : beam.beam_y)
			std::cout << i << '\t';
		std::cout << "\nk = " << k << std::endl;
		std::cout << "\bb = " << b << std::endl;
		// <-
	}

	void make_photo() {

	}

	void check_item() {

	}

	void get_photo() {

	}

	void get_camera_coord(double &x_, double &y_) {
		x_ = x;
		y_ = y;
	}

	const std::string get_camera_state() {
		switch (state)
		{
		case Camera_State::WAITING:
			return "waiting...";

		case Camera_State::MAKE_PHOTO:
			return "make a photo";

		case Camera_State::SEND_PHOTO:
			return "send a photo";

		case Camera_State::ROTATED:
			return "rotated";

		default:
			std::cout << "\n!!!\tDefault case print_camera_state()" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
};

class Robot
{
private:
	bool power{};
	double	x, y,
			angle{},
			azimuth{};
	Robot_State state{};

public:
	Robot(double x_, double y_)
		: x(x_), y(y_)
	{
	}



	void rotate() {
		
	}

	void move() {

	}

	void calc_azimuth() {

	}

	void take_object() {

	}

	void take_out_object() {

	}

	void set_robot_state(Robot_State state_) {
		state = state_;
	}

	const std::string get_robot_state() {
		switch (state)
		{
		case Robot_State::WAITING:
			return "waiting...";

		case Robot_State::MOVING_TO_TRASH:
			return "moving to trash";

		case Robot_State::MOVING_TO_TRASH_CAN:
			return "moving to trash can";

		case Robot_State::TAKE_TRASH:
			return "take the trash";

		case Robot_State::TAKE_OUT_TRASH:
			return "take out the trash";

		case Robot_State::ROTATED:
			return "rotated";

		default:
			std::cout << "\n!!!\tDefault case print_robot_state()" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
};

class Operator
{
public:
	void robot_on() {

	}

	void robot_off() {

	}

	void camera_on() {

	}

	void camera_off() {

	}


	const std::string get_robot_state(Robot &robot) {
		return robot.get_robot_state();
	}

	const std::string get_camera_state(Camera &camera) {
		return camera.get_camera_state();
	}
};

int main() {
	Item tresh(2.0, 3.0, Item_Type::TRASH);
	Robot a(2.2, 2.2);
	Operator b;
	a.set_robot_state(Robot_State::WAITING);
	std::cout << b.get_robot_state(a);
	a.set_robot_state(Robot_State::TAKE_OUT_TRASH);
	std::cout << a.get_robot_state();
	Camera camera(2.0, 2.0);
	camera.rotate();
	camera.print_beam();
	return 0;
}