#ifndef GAME_ENGINE_TIME_H
#define GAME_ENGINE_TIME_H

#include "../BasicTypes.h"

namespace Engine
{
	class Time : public object
	{
		CLASS_HEADER(Time)
	public:
		static Float32 GetTime();
		static Float32 GetDeltaTime();

	private:
		static Float32 s_Time;
		static Float32 s_DeltaTime;
		friend class Application;
		
	};

	TYPE_DEFINE(Time)
}

#endif