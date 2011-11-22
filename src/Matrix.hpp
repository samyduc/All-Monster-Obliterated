
///=============================================================================
///
/// \file           Matrix.hpp
/// \class          Matrix
///
/// \date           Creation date:  01/02/2009
/// \date           Latest update:  08/08/2009
///
/// \author         Benjamin Rimet, benjamin.rimet@gmail.com
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Represents a 4x4 transformation matrix.
///
///=============================================================================

// Include guard
#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED
//-----------------------------------------------------------------------------/

// Dependancies
#include <iostream>
#include <cmath>
#include "Triplet.hpp"
//-----------------------------------------------------------------------------/

template <class T>
class Matrix
{
// Methods
public:

    Matrix()
    {
        setIdentity();
    }

    void setIdentity()
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                   m_entry[i][j] = 1;
                else
                   m_entry[i][j] = 0;
            }
        }
    }

    Triplet<T> position() const
    {
        return (Triplet<T>(m_entry[3][0], m_entry[3][1], m_entry[3][2]));
    }

    void setPosition(Triplet<T> pos)
    {
        m_entry[3][0] = pos.x;
        m_entry[3][1] = pos.y;
        m_entry[3][2] = pos.z;
    }

    void setPosition(T x, T y, T z)
    {
        m_entry[3][0] = x;
        m_entry[3][1] = y;
        m_entry[3][2] = z;
    }

    void setRotationY(T rad)
    {
        T sine1 = sin(rad);
        T cosine1 = cos(rad);

        m_entry[0][0] = cosine1;
        m_entry[0][2] = -sine1;
        m_entry[2][0] = sine1;
        m_entry[2][2] = cosine1;
    }

    T rotationX()
    {
        T angle = acos(m_entry[1][1]);
        if (asin(m_entry[1][2]) < 0)
        {
            angle = -angle;
        }

        return (angle);
    }

    T rotationY()
    {
        T angle = acos(m_entry[0][0]);
        if (asin(m_entry[2][0]) < 0)
        {
            angle = -angle;
        }

        return (angle);
    }

    T rotationZ()
    {
        T angle = acos(m_entry[0][0]);
        if (asin(m_entry[0][1]) < 0)
        {
            angle = -angle;
        }

        return (angle);
    }

    T* raw()
    {
        return (&m_entry[0][0]);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
    {
        os << mat.m_entry[0][0] << ' ' << mat.m_entry[1][0] << ' ';
        os << mat.m_entry[2][0] << ' ' << mat.m_entry[3][0] << std::endl;
        os << mat.m_entry[0][1] << ' ' << mat.m_entry[1][1] << ' ';
        os << mat.m_entry[2][1] << ' ' << mat.m_entry[3][1] << std::endl;
        os << mat.m_entry[0][2] << ' ' << mat.m_entry[1][2] << ' ';
        os << mat.m_entry[2][2] << ' ' << mat.m_entry[3][2] << std::endl;
        os << mat.m_entry[0][3] << ' ' << mat.m_entry[1][3] << ' ';
        os << mat.m_entry[2][3] << ' ' << mat.m_entry[3][3] << std::endl;
        return os;
    }

// Properties
protected:
    T m_entry[4][4];
}; // Matrix

/// \brief Typedef for a Matrix using floats for its entries.
typedef Matrix<float> Matrix_f;

#endif // MATRIX_HPP_INCLUDED


