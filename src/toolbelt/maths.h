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

#ifndef MATHS_H
#define MATHS_H

#include <float.h>
#include <math.h>
#include <stdint.h>

#define real_t double
#define integer_t long

#define sec_t double
#define msec_t long

#define MATH_PI ((real_t)3.14159265358979323846264338327950288)

// Return the max of two real_t.
real_t math_max(real_t a, real_t b);

// Return the min of two real_t.
real_t math_min(real_t a, real_t b);

// Return the absolute value of a real_t.
real_t math_abs(real_t n);

// Clamp n to be between min and max.
real_t math_clamp(real_t n, real_t min, real_t max);

// Linearly interpolate (or extrapolate) between n1 and n2 by t
// percent.
real_t math_lerp(real_t n1, real_t n2, real_t t);

// Linearly interpolate from n1 to n2 by no more than d.
real_t math_lerpconst(real_t n1, real_t n2, real_t d);

#endif
