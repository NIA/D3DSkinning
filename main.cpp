#include "main.h"
#include "Application.h"
#include "cylinder.h"

INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, INT )
{
    srand( static_cast<unsigned>( time(NULL) ) );

    Vertex * cylinder_vertices;
    Index * cylinder_indices;
    try
    {
        Application app;
        
        cylinder_vertices = new Vertex[CYLINDER_VERTICES_COUNT];
        cylinder_indices = new Index[CYLINDER_INDICES_COUNT];
        
        const float height = 2.0f;
        cylinder( D3DXVECTOR3(0,0,-height/2), 0.7f, height, cylinder_vertices, cylinder_indices );

        Model cylinder( app.get_device(),
                        D3DPT_TRIANGLESTRIP,
                        cylinder_vertices,
                        CYLINDER_VERTICES_COUNT,
                        cylinder_indices,
                        CYLINDER_INDICES_COUNT,
                        CYLINDER_INDICES_COUNT - 2,
                        D3DXVECTOR3(0,0,-1));

        app.add_model(cylinder);
        app.run();
        delete_array(&cylinder_indices);
        delete_array(&cylinder_vertices);
    }
    catch(RuntimeError &e)
    {
        delete_array(&cylinder_indices);
        delete_array(&cylinder_vertices);
        const TCHAR *MESSAGE_BOX_TITLE = _T("Skinning error!");
        MessageBox(NULL, e.message(), MESSAGE_BOX_TITLE, MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
