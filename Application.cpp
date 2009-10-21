#include "Application.h"
#include <time.h>

namespace
{
    const char      *SHADER_FILE = "shader.vsh";
    const int        WINDOW_SIZE = 600;
    const D3DCOLOR   BACKGROUND_COLOR = D3DCOLOR_XRGB( 64, 64, 74 );
    const bool       INITIAL_WIREFRAME_STATE = true;
    const float      MORPHING_PERIOD = 1.9f;
    const float      MORPHING_OMEGA = 2.0f*D3DX_PI/MORPHING_PERIOD;

    const float      FINAL_RADIUS = 1.41f;

    const unsigned   D3DXVEC_SIZE = sizeof(D3DXVECTOR4);
}

class TetraFloat
// Contains 4 floats to give a constant float to a shader as a 4-vector
{
    float same_floats[D3DXVEC_SIZE];
public:
    TetraFloat(float f)
    {
        for(unsigned i = 0; i < D3DXVEC_SIZE - 1; ++i)
            same_floats[i] = f;
        same_floats[D3DXVEC_SIZE - 1] = 1.0f;
    }
    operator const float*() const { return same_floats; }
};

Application::Application() :
    d3d(NULL), device(NULL), vertex_decl(NULL), shader(NULL),
    window(WINDOW_SIZE, WINDOW_SIZE), camera(2.84f, 1.44f, 0.94f) // Constants selected for better view of pyramid
{
    try
    {
        init_device();
        init_shader();
    }
    catch(...)
    {
        release_interfaces();
        throw;
    }
}

void Application::init_device()
{
    d3d = Direct3DCreate9( D3D_SDK_VERSION );
    if( d3d == NULL )
        throw D3DInitError();

    // Set up the structure used to create the device
    D3DPRESENT_PARAMETERS present_parameters;
    ZeroMemory( &present_parameters, sizeof( present_parameters ) );
    present_parameters.Windowed = TRUE;
    present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    present_parameters.BackBufferFormat = D3DFMT_UNKNOWN;
    present_parameters.EnableAutoDepthStencil = TRUE;
    present_parameters.AutoDepthStencilFormat = D3DFMT_D16;
    // Create the device
    if( FAILED( d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &present_parameters, &device ) ) )
        throw D3DInitError();
    toggle_wireframe();
}

void Application::init_shader()
{
    if( FAILED( device->CreateVertexDeclaration(VERTEX_DECL_ARRAY, &vertex_decl) ) )
        throw VertexDeclarationInitError();

    ID3DXBuffer * shader_buffer = NULL;
    try
    {
        if( FAILED( D3DXAssembleShaderFromFileA( SHADER_FILE, NULL, NULL, NULL, &shader_buffer, NULL ) ) )
            throw VertexShaderAssemblyError();
        if( FAILED( device->CreateVertexShader( (DWORD*) shader_buffer->GetBufferPointer(), &shader ) ) )
            throw VertexShaderInitError();
    }
    catch(...)
    {
        release_interface(shader_buffer);
        throw;
    }
    release_interface(shader_buffer);
    
}

void Application::render()
{
    check_render( device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, BACKGROUND_COLOR, 1.0f, 0 ) );
    
    // Begin the scene
    check_render( device->BeginScene() );
    // Setup
    check_render( device->SetVertexDeclaration(vertex_decl) );
    check_render( device->SetVertexShader(shader) );
    // Setting constants
    //   c0 is the final radius
    check_render( device->SetVertexShaderConstantF(0, TetraFloat(FINAL_RADIUS), 1) );
    float time = static_cast<float>( clock() )/static_cast<float>( CLOCKS_PER_SEC );
    float t = (sin(MORPHING_OMEGA*time) + 1.0f)/2.0f; // parameter of morhing: 0 to 1
    //   c1 is the parameter t
    check_render( device->SetVertexShaderConstantF(1, TetraFloat(t), 1) );
    //   c2-c5 is the matrix
    check_render( device->SetVertexShaderConstantF(2, camera.get_matrix(), sizeof(D3DXMATRIX)/sizeof(D3DXVECTOR4)) );
    // Draw
    for ( std::list<Model*>::iterator iter = models.begin(); iter != models.end(); iter++ )
        (*iter)->draw();
    // End the scene
    check_render( device->EndScene() );
    
    // Present the backbuffer contents to the display
    check_render( device->Present( NULL, NULL, NULL, NULL ) );

}

IDirect3DDevice9 * Application::get_device()
{
    return device;
}

void Application::add_model(Model &model)
{
    models.push_back( &model );
}

void Application::remove_model(Model &model)
{
    models.remove( &model );
}

void Application::process_key(unsigned code)
{
    switch( code )
    {
    case VK_ESCAPE:
        PostQuitMessage( 0 );
        break;
    case VK_UP:
    case 'W':
        camera.move_up();
        break;
    case VK_DOWN:
    case 'S':
        camera.move_down();
        break;
    case VK_PRIOR:
    case VK_ADD:
    case VK_OEM_PLUS:
        camera.move_nearer();
        break;
    case VK_NEXT:
    case VK_SUBTRACT:
    case VK_OEM_MINUS:
        camera.move_farther();
        break;
    case VK_LEFT:
    case 'A':
        camera.move_clockwise();
        break;
    case VK_RIGHT:
    case 'D':
        camera.move_counterclockwise();
        break;
    case VK_SPACE:
        toggle_wireframe();
        break;
    }
}

void Application::run()
{
    window.show();
    window.update();

    // Enter the message loop
    MSG msg;
    ZeroMemory( &msg, sizeof( msg ) );
    while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
            if( msg.message == WM_KEYDOWN )
            {
                process_key( static_cast<unsigned>( msg.wParam ) );
            }

            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
            render();
    }
}

void Application::toggle_wireframe()
{
    static bool wireframe = !INITIAL_WIREFRAME_STATE;
    wireframe = !wireframe;

    if( wireframe )
    {
        check_state( device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ) );
        check_state( device->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME ) );
    }
    else
    {
        check_state( device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW ) );
        check_state( device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID ) );
    }
}

void Application::release_interfaces()
{
    release_interface( d3d );
    release_interface( device );
    release_interface( vertex_decl );
    release_interface( shader );
}

Application::~Application()
{
    release_interfaces();
}