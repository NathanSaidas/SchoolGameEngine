#ifndef GAME_ENGINE_VECTOR_2_H
#define GAME_ENGINE_VECTOR_2_H

#include "../BasicTypes.h"
#include <glm\glm.hpp>

namespace Engine
{
	class Vector2 : public object, public glm::vec2
	{
		CLASS_HEADER(Vector2)
	public:
		Vector2();
		Vector2(Float32 x, Float32 y);
		Vector2(const Vector2 & aVec);
		Vector2(const glm::vec2 & aVec);
		~Vector2();

		static float Angle(const Vector2 & aFrom, const Vector2 & aTo);
		static Vector2 ClampMagnitude(const Vector2 & aVector, float aMaxLength);
		static float Distance(const Vector2 & aFrom, const Vector2 & aTo);
		static float Dot(const Vector2 & aFrom, const Vector2 & aTo);
		static Vector2 Lerp(const Vector2 & aFrom, const Vector2 & aTo, float aTime);
		
		
		static Vector2 Reflect(const Vector2 & aIncident, const Vector2 & aNormal);
		static Vector2 Refract(const Vector2 & aIncident, const Vector2 & aNormal, const float & aTheta);
		static Vector2 FaceForward(const Vector2 & aNormal, const Vector2 & aIncident, const Vector2 & aNormalRef);

		void Scale(const Vector2 & aScale);
		void Scale(const float & aX, const float & aY);
		float GetMagnitude();
		float GetSqrMagnitude();
		Vector2 Normalized();
		void Normalize();

		//Converts the data into raw 16 bit format. (8 bytes)
		glm::vec2 Raw() const;
	private:
		
	};

	TYPE_DEFINE(Vector2)
	TYPE_DEFINE_PTR(Vector2*, "Vector2 Ptr")
}

#endif