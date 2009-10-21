#include "Model.h"

Model::Model(   IDirect3DDevice9 *device, D3DPRIMITIVETYPE primitive_type, const Vertex *vertices,
                unsigned vertices_count, const Index *indices, unsigned indices_count,
                unsigned primitives_count )

: device(device), vertices_count(vertices_count), primitives_count(primitives_count),
  primitive_type(primitive_type), vertex_buffer(NULL), index_buffer(NULL)
{
    _ASSERT(vertices != NULL);
    _ASSERT(indices != NULL);
    try
    {
        const unsigned vertices_size = vertices_count*sizeof(vertices[0]);
        const unsigned indices_size = indices_count*sizeof(indices[0]);

        if(FAILED( device->CreateVertexBuffer( vertices_size, 0, 0, D3DPOOL_DEFAULT, &vertex_buffer, NULL ) ))
            throw VertexBufferInitError();
        

        if(FAILED( device->CreateIndexBuffer( indices_size, 0, INDEX_FORMAT, D3DPOOL_DEFAULT, &index_buffer, NULL ) ))
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

void Model::release_interfaces()
{
    release_interface(vertex_buffer);
    release_interface(index_buffer);
}

Model::~Model()
{
    release_interfaces();
}