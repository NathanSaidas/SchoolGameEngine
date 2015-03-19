#ifndef GAME_ENGINE_QUATERNION_H
#define GAME_ENGINE_QUATERNION_H

#include "../BasicTypes.h"
#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>

namespace Engine
{
    class Vector3;
    class Matrix4x4;

    class Quaternion : public object, public glm::quat
    {
        CLASS_HEADER(Quaternion)
    public:
        Quaternion();
        Quaternion(glm::quat & aQuat);
        ~Quaternion();

        static float Angle(const Quaternion & aQuatA, const Quaternion & aQuatB);
        static float Dot(const Quaternion & aQuatA, const Quaternion & aQuatB);
        static Quaternion Inverse(const Quaternion & aRotation);
        static Quaternion Euler(const Vector3 & aEulerAngles);
        static Quaternion LookRotation(const Vector3 & aLookDirection);
        static Quaternion LookRotation(const Vector3 & aLookDirection, const Vector3 & aDesiredUp);
        static Quaternion Slerp(const Quaternion & aFrom, const Quaternion & aTo, const Float32 & aTime);

        static Quaternion RotationBetween(Vector3 aStart, Vector3 aEnd);
        
        Vector3 GetEulerAngles() const;
        Matrix4x4 GetRotationMatrix() const;
        
        glm::quat Raw() const;
    };

    TYPE_DEFINE(Quaternion)
    TYPE_DEFINE_PTR(Quaternion*, "Quaternion Ptr")
}

#endif