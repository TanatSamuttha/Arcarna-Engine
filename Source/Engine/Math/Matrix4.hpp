#pragma once

#include <utility>

namespace Arcana::Math
{
    class Matrix4
    {
    private:
        float Value[4][4];

    public:
        Matrix4 () : Value {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
        {}
    
        Matrix4 (
            float R0C0, float R0C1, float R0C2, float R0C3,
            float R1C0, float R1C1, float R1C2, float R1C3,
            float R2C0, float R2C1, float R2C2, float R2C3,
            float R3C0, float R3C1, float R3C2, float R3C3
        ) : Value {
            {R0C0, R0C1, R0C2, R0C3},
            {R1C0, R1C1, R1C2, R1C3},
            {R2C0, R2C1, R2C2, R2C3},
            {R3C0, R3C1, R3C2, R3C3}
        }
        {}

        float& operator() (int Row, int Column)
        {
            return Value[Row][Column];
        }

        Matrix4 Transpose ()
        {
            Matrix4 Result;
            for (int i = 0; i < 4; ++i)
            {
                for (int j = i + 1; j < 4; ++j)
                {
                    Result(i, i) = Value[i][i];
                    Result(i, j) = Value[j][i];
                    Result(j, i) = Value[i][j];
                }
            }
        }

        Matrix4 operator+ (Matrix4& RHS) const
        {
            Matrix4 Result;
            for (int Row = 0; Row < 4; ++Row)
            {
                for (int Column = 0; Column < 4; ++Column)
                {
                    Result(Row, Column) = this->Value[Row][Column] + RHS(Row, Column);
                }
            }

            return Result;
        }

        Matrix4 operator* (Matrix4& RHS) const
        {
            Matrix4 Result;
            for (int Row = 0; Row < 4; ++Row)
            {
                for (int Column = 0; Column < 4; ++Column)
                {
                    float Sum = 0;
                    for (int k = 0; k < 4; ++k)
                    {
                        Sum += this->Value[Row][k] * RHS(k, Column);
                    }
                    Result(Row, Column) = Sum;
                }
            }

            return Result;
        }
    };
}