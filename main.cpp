/*	*****************************************************************
	Практика 2-го курса студентов МАИ

	Задание '4'		"Программа для роя роботов, которые убирают мусор; 
					 в заданное место в комнате"

	Выполнили:		Логунов Д.С.;
					Смыслов И.В.; 
					Шемяков В.О.;	(гр. М3О-214Б-19)

	Проверил:		Максимов А.Н.
	*****************************************************************/	

#include <cmath>
#include <vector>


#include "enum_states.h"

#include "item.h"
#include "admin.h"
#include "camera.h"
#include "robot.h"

int main() {
	Item trash(2.0, 2.0, Item_Type::TRASH, Item_Form::RECTANGLE);
	Robot robot(2.2, 2.2);
	Admin admin;
	robot.set_state(Robot_State::WAITING);
	std::cout << admin.get_robot_state(robot);
	robot.set_state(Robot_State::TAKE_OUT_TRASH);
	std::cout << robot.get_state();
	Camera camera(0.0, 0.0);

	std::cout << trash.get_item_type();
	trash.make_volume(Item_Form::RECTANGLE);
	camera.set_item_point(trash);
	camera.draw_beam();
	return 0;
}