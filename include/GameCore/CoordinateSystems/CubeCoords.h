#ifndef CUBECOORDS_H
#define CUBECOORDS_H

#include <functional>

// These coordinates define the hexagonal map. This is the primary basis for this
//  map. In to keep things "simple", this struct intends to be Plain Old Data,
//  not having any member functions ( this is just a note to myself so I don't forget )
struct cube_coords_t
{
    int x, y, z;
    friend cube_coords_t operator+(const cube_coords_t& c1, const cube_coords_t& c2);
    friend cube_coords_t operator-(const cube_coords_t& c1, const cube_coords_t& c2);
    friend bool operator==(const cube_coords_t& c1, const cube_coords_t& c2);
};

//! Not implemented!
// Hashing function for cube coordinates. these coordinates are used as keys for
//  maps (ie world_data), and because cube_coords_t is a structure I defined, I
//  need to create a hashing function for it as well.
struct cubeHash
{
    std::size_t operator()(cube_coords_t const& c) const noexcept;
};

#endif