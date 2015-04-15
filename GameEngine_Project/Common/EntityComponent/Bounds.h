#ifndef GAME_ENGINE_BOUNDS_H
#define GAME_ENGINE_BOUNDS_H

#include "../BasicTypes.h"
#include "../Math/Math.h"

namespace Engine
{
    class Bounds : public object
    {
        RDECLARE_CLASS(Bounds)

    public:
        Bounds();
        Bounds(const Vector3 & aMin, const Vector3 & aMax);
        ~Bounds();

        inline Vector3 GetMin()
        {
            return m_Min;
        }
        inline Vector3 GetMax()
        {
            return m_Max;
        }

        inline void SetMin(const Vector3 & aMin)
        {
            m_Min = aMin;
        }
        inline void SetMax(const Vector3 & aMax)
        {
            m_Max = aMax;
        }

    private:
        Vector3 m_Min;
        Vector3 m_Max;
    };

    TYPE_DEFINE(Bounds)
}

#endif