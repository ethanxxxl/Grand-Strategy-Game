#ifndef PIXELCOORDS_H
#define PIXELCOORDS_H

namespace GameCore
{
    // Pixel are cube or axial coordinates, but in a standard (x,y) basis. as of now, these
    //  are only used in generating terrain.
    // Note: these must be of type double, because of the change of basis that occurs with axial/cube
    //  coordinates.
    struct pixel_coords_t
    {
        double x, y;
    };
}

#endif