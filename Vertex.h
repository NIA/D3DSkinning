#pragma once
#include "main.h"

typedef DWORD Index;
extern const D3DFORMAT INDEX_FORMAT;

// It must be a macro, not a constant, because it must be known at compile-time (it is used for array initialization)
#define VERTICES_PER_TRIANGLE 3

inline int rand_col_comp()
// Returns random color component: an integer between 0 and 255
{
    return rand()*255/RAND_MAX;
}

class Vertex
{
public:
    D3DXVECTOR3 pos;            // The position for the vertex
    D3DCOLOR color;             // The vertex color
    float weights[BONES_COUNT]; // Weights for skinning
private:
    void set_weight(float weight)
    {
        weights[0] = weight;
        weights[1] = 1 - weight;
    }
public:
    Vertex() : pos(), color(0)
    {
        set_weight(1.0f);
    }
    Vertex(D3DXVECTOR3 pos, D3DCOLOR color, float weight) : pos(pos), color(color)
    {
        set_weight(weight);
    }
    Vertex(D3DXVECTOR3 pos, float weight) : pos(pos)
    {
        color = D3DCOLOR_XRGB( rand_col_comp(), rand_col_comp(), rand_col_comp() );
        set_weight(weight);
    }
};

extern const D3DVERTEXELEMENT9 VERTEX_DECL_ARRAY[];
