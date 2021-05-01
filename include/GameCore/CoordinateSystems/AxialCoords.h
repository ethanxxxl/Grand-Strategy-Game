#ifndef AXIALCOORDS_H
#define AXIALCOORDS_H

// axial coordinates, similar to cube coords, but they
//  take advantage of property of cube coords that the sum
//  of all three components is zero.
struct axial_coords_t 
{
    int q, r; 
};

#endif
