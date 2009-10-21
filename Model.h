#pragma once
#include "main.h"
#include "Vertex.h"

class Model
{
private:
    IDirect3DDevice9        *device;

    unsigned    vertices_count;
    unsigned    primitives_count;

    D3DPRIMITIVETYPE        primitive_type;
    IDirect3DVertexBuffer9  *vertex_buffer;
    IDirect3DIndexBuffer9   *index_buffer;

    void release_interfaces();

public:
    Model(  IDirect3DDevice9 *device,
            D3DPRIMITIVETYPE primitive_type,
            const Vertex *vertices,
            unsigned vertices_count,
            const Index *indices,
            unsigned indices_count,
            unsigned primitives_count );
    
    virtual void draw() const;

    virtual ~Model();
};