#ifndef ENUM_STATE_H
#define ENUM_STATE_H

enum class Robot_State
{
	WAITING,
	MOVING_TO_TRASH,
	MOVING_TO_TRASH_CAN,
	TAKE_TRASH,
	TAKE_OUT_TRASH,
	ROTATED,
	ROTATED_TO_TRASH_CAN,
	COLLISION,
	COLLISION_WAIT,
	MAX_ROBOT_STATE
};

enum class Camera_State
{
	WAITING,
	DETECTED,
	MAKE_PHOTO,
	SEND_PHOTO,
	ROTATED,
	MAX_CAMERA_STATE
};

enum class Item_Type
{
	TRASH,
	NOT_TRASH,
	TRASH_CAN,
	MAX_ITEM_TYPE
};

enum class Item_Form
{
	RECTANGLE,
	CIRCLE,
	MAX_ITEM_FORM
};

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
#endif // !ENUM_STATE_H