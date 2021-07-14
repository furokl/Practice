#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

namespace control_system
{
	const char
		file[] = "C:\\Users\\User\\source\\repos\\RoboTrash_SFML\\redist\\";

	const float
		camera_rotate{ 0.05f },
		robot_rotate{ 1.f },
		robot_step{ 0.15f },
		beam_step{ 0.05f };

	const int
		camera_displacement{ -13 },
		robot_displacement{ -25 },
		item_displacement{ -15 },
		can_displacement{ -25 },
		circle_displacement{ -150 },

		item_stretch{ 20 },
		beam_circle{ 150 },
		sound_master{ 15 },
		robot_detect{ 30 },
		robot_throw{ 10 },
		beam_range{ static_cast<int>((1.f / beam_step) * 150) };
}

#endif // !CONTROL_SYSTEM_H
