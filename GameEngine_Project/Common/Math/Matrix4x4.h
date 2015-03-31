#ifndef GAME_ENGINE_MATRIX_4_4_H
#define GAME_ENGINE_MATRIX_4_4_H

#include "../BasicTypes.h"
#include <glm\glm.hpp>

namespace Engine
{
    class Vector2;
    class Vector3;
    class Vector4;
    class Quaternion;

    class Matrix4x4 : public object, public glm::mat4
    {
        CLASS_HEADER(Matrix4x4)
    public:
        Matrix4x4();
        Matrix4x4(const glm::mat4x4 & aMatrix);
        ~Matrix4x4();


        static Matrix4x4 Transpose(const Matrix4x4 & aMatrix);
        static Matrix4x4 Inverse(const Matrix4x4 & aMatrix);
        static Matrix4x4 Scale(const Matrix4x4 & aMatrix, const Vector3 & aScale);
        static Matrix4x4 Translate(const Matrix4x4 & aMatrix, const Vector3 & aTranslation);
        static Matrix4x4 Rotate(const Matrix4x4 & aMatrix, const Float32 & aRotation, const Vector3 & aAxis);
        static Matrix4x4 Rotate(const Matrix4x4 & aMatrix, const Vector3 & aRotation);
        static Matrix4x4 Ortho(const Float32 & aLeft, const Float32 & aRight, const Float32 & aTop, const Float32 & aBottom, const Float32 & aFar, const Float32 & aNear);
        static Matrix4x4 Perspective(const Float32 & aFOV, const Float32 & aAspectRatio, const Float32 & aNear, const Float32 & aFar);
        static Matrix4x4 LookAt(const Vector3 & aCameraPosition, const Vector3 & aTargetPosition, const Vector3 & aUpDirection);
        static Matrix4x4 Identity();
		static Matrix4x4 TRS(const Vector3 & aPosition, const Vector3 & aRotation, const Vector3 & aScale);
        
        void Transpose();
        void Inverse();
        void Scale(const Vector3 & aScale);
        void Translate(const Vector3 & aTranslation);
        void Rotate(const Float32 & aRotation, const Float32 & aAngle, const Vector3 & aAxis);
        void Rotate(const Vector3 & aRotation);
        void SetIdentity();
        Quaternion GetRotation() const;


        glm::mat4 Raw() const;

		Matrix4x4 operator*=(const Matrix4x4 & aMatrix)
		{
			glm::mat4 a = Raw();
			glm::mat4 b = aMatrix.Raw();
			*this = a * b;
			return *this;
		}

		Matrix4x4 operator *(const Matrix4x4 & aMatrix)
		{
			glm::mat4 a = Raw();
			glm::mat4 b = aMatrix.Raw();
			return a * b;
		}
        

    };

    TYPE_DEFINE(Matrix4x4)
}

#endif