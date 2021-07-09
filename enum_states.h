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
#endif // !ENUM_STATE_H