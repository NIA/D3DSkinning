#pragma once

#include "main.h"

inline D3DXMATRIX shift_matrix(D3DXVECTOR3 shift)
{
    return D3DXMATRIX(  1, 0, 0, shift.x,
                        0, 1, 0, shift.y,
                        0, 0, 1, shift.z,
                        0, 0, 0, 1 );
}

inline D3DXMATRIX rotate_x_matrix(float angle)
{
    return D3DXMATRIX( 1,           0,          0, 0,
                       0,  cos(angle), sin(angle), 0,
                       0, -sin(angle), cos(angle), 0,
                       0,           0,          0, 1 );
}

inline D3DXMATRIX rotate_x_matrix(float angle, D3DXVECTOR3 center)
{
    return shift_matrix(center)*rotate_x_matrix(angle)*shift_matrix(-center) ;
}
