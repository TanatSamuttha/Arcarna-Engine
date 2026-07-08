#pragma once

namespace Arcarna
{
    class Physics
    {
    private:
        static float Gravity;
        static float dt;

    public:

        void Update (const float dt)
        {
            this->dt = dt;
        }

        float Getdt ()
        {
            return dt;
        }

        void SetGravity (const float Gravity)
        {
            this->Gravity = Gravity;
        }
    };
}