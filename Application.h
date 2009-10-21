#pragma once
#include "main.h"
#include "Camera.h"
#include "Window.h"
#include "Vertex.h"
#include "Model.h"

#pragma warning( disable : 4996 ) // disable deprecated warning 
#pragma warning( disable : 4995 ) // disable deprecated warning 
#include <list>
#pragma warning( default : 4996 ) // disable deprecated warning
#pragma warning( default : 4995 ) // disable deprecated warning 

class Application
{
private:
    IDirect3D9                  *d3d;           // used to create the D3DDevice
    IDirect3DDevice9            *device;        // our rendering device
    IDirect3DVertexDeclaration9 *vertex_decl;   // vertex declaration
    IDirect3DVertexShader9      *shader;        // vertex shader

    Window window;

    std::list<Model*> models;

    Camera camera;

    // Initialization steps:
    void init_device();
    void init_shader();

    void process_key(unsigned code);

    void render();

    // Deinitialization steps:
    void release_interfaces();

public:
    Application();
    IDirect3DDevice9 * get_device();

    void add_model(Model &model);
    void remove_model(Model &model);
    void run();

    void toggle_wireframe();

    ~Application();

};
