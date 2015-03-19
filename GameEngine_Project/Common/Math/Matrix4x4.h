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
    struct Frustum;

    class Matrix4x4 : public object, public glm::mat4x4
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
        static Matrix4x4 Ortho(const Frustum & aFrustum);
        static Matrix4x4 Perspective(const Float32 & aFOV, const Float32 & aAspectRatio, const Float32 & aNear, const Float32 & aFar);
        static Matrix4x4 LookAt(const Vector3 & aCameraPosition, const Vector3 & aTargetPosition, const Vector3 & aUpDirection);
        static Matrix4x4 Identity();
        
        void Transpose();
        void Inverse();
        void Scale(const Vector3 & aScale);
        void Translate(const Vector3 & aTranslation);
        void Rotate(const Float32 & aRotation, const Float32 & aAngle, const Vector3 & aAxis);
        void Rotate(const Vector3 & aRotation);
        void SetIdentity();
        Quaternion GetRotation() const;


        glm::mat4x4 Raw() const;
        

    };

    TYPE_DEFINE(Matrix4x4)
    TYPE_DEFINE_PTR(Matrix4x4*, "Matrix2x2 Ptr")
}

#endif