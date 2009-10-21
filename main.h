#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>
#include "Error.h"

inline void release_interface(IUnknown* iface)
{
    if( iface != NULL )
        iface->Release();
}

template<class Type> void delete_array(Type **dynamic_array)
{
    _ASSERT(dynamic_array != NULL);
    if( *dynamic_array != NULL)
    {
        delete[] *dynamic_array;
        *dynamic_array = NULL;
    }
}
