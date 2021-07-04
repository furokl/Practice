#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

namespace control_system
{
	const double
		camera_rotate{ 0.05 },
		robot_step{ 0.05 },
		beam_step{ 0.05 };

	const int
		camera_displacement{ 13 },
		beam_range{ static_cast<int>((1.0 / beam_step) * 150) };
}

#endif // !CONTROL_SYSTEM_H
