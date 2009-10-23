#include "Model.h"
#include "matrices.h"

namespace
{
    const float SKINNING_PERIOD = 2.0f;
    const float SKINNING_OMEGA = 2.0f*D3DX_PI/SKINNING_PERIOD;
}

Model::Model(   IDirect3DDevice9 *device, D3DPRIMITIVETYPE primitive_type, const Vertex *vertices,
                unsigned vertices_count, const Index *indices, unsigned indices_count,
                unsigned primitives_count, D3DXVECTOR3 rotate_center )

: device(device), vertices_count(vertices_count), primitives_count(primitives_count),
  primitive_type(primitive_type), vertex_buffer(NULL), index_buffer(NULL), rotate_center(rotate_center)
{
    _ASSERT(vertices != NULL);
    _ASSERT(indices != NULL);
    try
    {
        const unsigned vertices_size = vertices_count*sizeof(vertices[0]);
        const unsigned indices_size = indices_count*sizeof(indices[0]);

        if(FAILED( device->CreateVertexBuffer( vertices_size, D3DUSAGE_WRITEONLY, 0, D3DPOOL_DEFAULT, &vertex_buffer, NULL ) ))
            throw VertexBufferInitError();
        

        if(FAILED( device->CreateIndexBuffer( indices_size, D3DUSAGE_WRITEONLY, INDEX_FORMAT, D3DPOOL_DEFAULT, &index_buffer, NULL ) ))
            throw IndexBufferInitError();
                    

        // fill the vertex buffer.
        VOID* vertices_to_fill;
        if(FAILED( vertex_buffer->Lock( 0, vertices_size, &vertices_to_fill, 0 ) ))
            throw VertexBufferFillError();
        memcpy( vertices_to_fill, vertices, vertices_size );
        vertex_buffer->Unlock();

        // fill the index buffer.
        VOID* indices_to_fill;
        if(FAILED( index_buffer->Lock( 0, indices_size, &indices_to_fill, 0 ) ))
            throw IndexBufferFillError();
        memcpy( indices_to_fill, indices, indices_size );
        index_buffer->Unlock();

        _ASSERT( BONES_COUNT <= sizeof(D3DXVECTOR4) ); // to fit weights into vertex shader register
        for(unsigned i = 0; i < BONES_COUNT; ++i)
            bones[i] = rotate_x_matrix(0.0f);
    }
    catch(...)
    {
        release_interfaces();
        throw;
    }
}

void Model::draw() const
{
    check_render( device->SetStreamSource( 0, vertex_buffer, 0, sizeof(Vertex) ) );
    check_render( device->SetIndices( index_buffer ) );
    check_render( device->DrawIndexedPrimitive( primitive_type , 0, 0, vertices_count, 0, primitives_count ) );
}

void Model::set_bones(float time)
{
    // first bone will set the rotation
    float angle = D3DX_PI/4.0f*sin(SKINNING_OMEGA*time);
    bones[0] = rotate_x_matrix( angle, rotate_center );
    // others will still be a unity matrix
}

const D3DXMATRIX &Model::get_bone(unsigned number) const
{
    _ASSERT( number < BONES_COUNT );
    return bones[number];
}

void Model::release_interfaces()
{
    release_interface(vertex_buffer);
    release_interface(index_buffer);
}

Model::~Model()
{
    release_interfaces();
}