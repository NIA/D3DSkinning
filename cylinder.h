#pragma once
#include "main.h"
#include "Vertex.h"

extern const Index CYLINDER_EDGES_PER_BASE;
extern const Index CYLINDER_EDGES_PER_HEIGHT;

extern const Index CYLINDER_VERTICES_COUNT;
extern const DWORD CYLINDER_INDICES_COUNT; // Calculated for TRIANGLESTRIP primitive type

// Writes data into arrays given as `res_vertices' and `res_indices',
void cylinder( D3DXVECTOR3 base_center, float radius, float height,
                Vertex *res_vertices, Index *res_indices);
