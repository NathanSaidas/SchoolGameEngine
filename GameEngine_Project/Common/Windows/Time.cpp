#include "Time.h"

namespace Engine
{
	Float32 Time::s_Time = 0.0f;
	Float32 Time::s_DeltaTime = 0.0f;

	Float32 Time::GetTime()
	{
		return s_Time;
	}
	Float32 Time::GetDeltaTime()
	{
		return s_DeltaTime;
	}
}