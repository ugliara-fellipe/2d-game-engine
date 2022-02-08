/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "toolbelt/maths.h"
#include <stdbool.h>

typedef struct v2d_s {
  real_t x;
  real_t y;
} v2d_t;

// Constant for the zero vector
extern v2d_t v2d_zero;

// Constant for the one vector
extern v2d_t v2d_one;

// Constructor for v2d structs
v2d_t v2d_init(const real_t x, const real_t y);

// Check if two vectors are equal
bool v2d_equal(v2d_t v1, v2d_t v2);

// Add two vectors
v2d_t v2d_add(v2d_t v1, v2d_t v2);

// Subtract two vectors
v2d_t v2d_sub(v2d_t v1, v2d_t v2);

// Multiplication two vectors
v2d_t v2d_mult(v2d_t v1, v2d_t v2);

// Negate a vector
v2d_t v2d_neg(v2d_t v);

// Scalar multiplication
v2d_t v2d_mult_sclr(v2d_t v, real_t s);

// Vector dot product
real_t v2d_dot(v2d_t v1, v2d_t v2);

// 2D vector cross product analog
real_t v2d_cross(v2d_t v1, v2d_t v2);

// Returns a perpendicular vector (90 degree rotation)
v2d_t v2d_perp(v2d_t v);

// Returns a perpendicular vector (-90 degree rotation)
v2d_t v2d_rperp(v2d_t v);

// Returns the vector projection of v1 onto v2
v2d_t v2d_project(v2d_t v1, v2d_t v2);

// Returns the unit length vector for the given angle (in radians)
v2d_t v2d_forangle(real_t a);

// Returns the angular direction v is pointing in (in radians)
real_t v2d_toangle(v2d_t v);

// Uses complex number multiplication to rotate v1 by v2. Scaling will occur if
// v1 is not a unit vector
v2d_t v2d_rotate(v2d_t v1, v2d_t v2);

// Inverse of v2d_rotate()
v2d_t v2d_unrotate(v2d_t v1, v2d_t v2);

// Returns the squared length of v. Faster than v2d_length() when you only need
// to compare lengths
real_t v2d_lengthsq(v2d_t v);

// Returns the length of v
real_t v2d_length(v2d_t v);

// Linearly interpolate between v1 and v2
v2d_t v2d_lerp(v2d_t v1, v2d_t v2, real_t t);

// Returns a normalized copy of v
v2d_t v2d_normalize(v2d_t v);

// Spherical linearly interpolate between v1 and v2
v2d_t v2d_slerp(v2d_t v1, v2d_t v2, real_t t);

// Spherical linearly interpolate between v1 towards v2 by no more than angle a
// radians
v2d_t v2d_slerpconst(v2d_t v1, v2d_t v2, real_t a);

// Clamp v to length len
v2d_t v2d_clamp(v2d_t v, real_t len);

// Linearly interpolate between v1 towards v2 by distance d
v2d_t v2d_lerpconst(v2d_t v1, v2d_t v2, real_t d);

// Returns the distance between v1 and v2
real_t v2d_dist(v2d_t v1, v2d_t v2);

// Returns the squared distance between v1 and v2. Faster than v2d_dist() when
// you only need to compare distances
real_t v2d_distsq(v2d_t v1, v2d_t v2);

// Returns true if the distance between v1 and v2 is less than dist
bool v2d_near(v2d_t v1, v2d_t v2, real_t dist);

#endif
