#include "main.h"
#include "Application.h"

INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, INT )
{
    srand( static_cast<unsigned>( time(NULL) ) );

    try
    {
        Application app;

        const Index PLANES_PER_PYRAMID = 8;
        const Vertex pyramid_vertices[]=
        {
            Vertex(D3DXVECTOR3(  1.0f, -1.0f,  0.00f )),
            Vertex(D3DXVECTOR3( -1.0f, -1.0f,  0.00f )),
            Vertex(D3DXVECTOR3( -1.0f,  1.0f,  0.00f )),
            Vertex(D3DXVECTOR3(  1.0f,  1.0f,  0.00f )),
            Vertex(D3DXVECTOR3(  0.0f,  0.0f,  1.41f )),
            Vertex(D3DXVECTOR3(  0.0f,  0.0f, -1.41f )),
        };
        const unsigned VERTICES_COUNT = sizeof(pyramid_vertices)/sizeof(pyramid_vertices[0]);
        const Index pyramid_indices[PLANES_PER_PYRAMID*VERTICES_PER_TRIANGLE] =
        {
            0, 4, 3,
            3, 4, 2,
            2, 4, 1,
            1, 4, 0,

            0, 3, 5,
            3, 2, 5,
            2, 1, 5,
            1, 0, 5,
        };
        const unsigned INDICES_COUNT = sizeof(pyramid_indices)/sizeof(pyramid_indices[0]);

        Model pyramid(  app.get_device(),
                        D3DPT_TRIANGLELIST,
                        pyramid_vertices,
                        VERTICES_COUNT,
                        pyramid_indices,
                        INDICES_COUNT,
                        INDICES_COUNT/VERTICES_PER_TRIANGLE );

        app.add_model(pyramid);
        app.run();
    }
    catch(RuntimeError &e)
    {
        const TCHAR *MESSAGE_BOX_TITLE = _T("Morphing error!");
        MessageBox(NULL, e.message(), MESSAGE_BOX_TITLE, MB_OK | MB_ICONERROR);
        return -1;
    }
    return 0;
}
