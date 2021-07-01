/*	*****************************************************************
	Практика 2-го курса студентов МАИ

	Задание '4'		"Программа для роя роботов, которые убирают мусор; 
					 в заданное место в комнате"

	Выполнили:		Логунов Д.С.;
					Смыслов И.В.; 
					Шемяков В.О.;	(гр. М3О-214Б-19)

	Проверил:		Максимов А.Н.
	*****************************************************************/	

#include <iostream>
#include <cmath>
#include <vector>


#include "enum_states.h"

#include "item.h"
#include "admin.h"
#include "camera.h"
#include "robot.h"

int main() {
	Item tresh(2.0, 3.0, Item_Type::TRASH);
	Robot a(2.2, 2.2);
	Admin b;
	a.set_state(Robot_State::WAITING);
	std::cout << b.get_robot_state(a);
	a.set_state(Robot_State::TAKE_OUT_TRASH);
	std::cout << a.get_state();
	Camera camera(2.0, 2.0);
	camera.draw_beam();
	return 0;
}