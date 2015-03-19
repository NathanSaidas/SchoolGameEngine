#ifndef GAME_ENGINE_VECTOR_3_H
#define GAME_ENGINE_VECTOR_3_H

#include "../BasicTypes.h"
#include <glm\glm.hpp>

namespace Engine
{
    class Vector4;

    class Vector3 : public object, public glm::vec3
    {
        CLASS_HEADER(Vector3)
    public:
        Vector3();
        Vector3(Float32 x, Float32 y, Float32 z);
        Vector3(const Vector3 & aVec);
        Vector3(const glm::vec3 & aVec);
        Vector3(const Vector4 & aVec);
        ~Vector3();

        static float Angle(const Vector3 & aFrom, const Vector3 & aTo);
        static Vector3 ClampMagnitude(const Vector3 & aVector, float aMaxLength);
        static float Distance(const Vector3 & aFrom, const Vector3 & aTo);
        static float Dot(const Vector3 & aFrom, const Vector3 & aTo);
        static Vector3 Cross(const Vector3 & aX, const Vector3 & aY);
        static Vector3 Lerp(const Vector3 & aFrom, const Vector3 & aTo, float aTime);

        static Vector3 Reflect(const Vector3 & aIncident, const Vector3 & aNormal);
        static Vector3 Refract(const Vector3 & aIncident, const Vector3 & aNormal, const float & aTheta);
        static Vector3 FaceForward(const Vector3 & aNormal, const Vector3 & aIncident, const Vector3 & aNormalRef);
        static Vector3 RotateX(const Vector3 & aVec, float aAngle);
        static Vector3 RotateY(const Vector3 & aVec, float aAngle);
        static Vector3 RotateZ(const Vector3 & aVec, float aAngle);
        
        void Scale(const Vector3 & aScale);
        void Scale(const float & aX, const float & aY, const float & aZ);
        float GetMagnitude() const;
        float GetSqrMagnitude() const;
        Vector3 Normalized() const;
        void Normalize();

        //Converts the data into raw 8 bit format. (12 bytes)
        glm::vec3 Raw() const;

        inline static Vector3 Up()
        {
            return Vector3(0.0, 1.0f, 0.0f);
        }
        inline static Vector3 Down()
        {
            return Vector3(0.0, -1.0f, 0.0f);
        }
        inline static Vector3 Left()
        {
            return Vector3(-1.0, 0.0f, 0.0f);
        }
        inline static Vector3 Right()
        {
            return Vector3(1.0, 0.0f, 0.0f);
        }
        inline static Vector3 Forward()
        {
            return Vector3(0.0, 0.0f, 1.0f);
        }
        inline static Vector3 Back()
        {
            return Vector3(0.0, 0.0f, -1.0f);
        }
    private:

    };

    TYPE_DEFINE(Vector3)
    TYPE_DEFINE_PTR(Vector3*, "Vector3 Ptr")
}

#endif