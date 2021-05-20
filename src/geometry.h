/* Copyright (c) 2012, Bastien Dejean
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BSPWM_GEOMETRY_H
#define BSPWM_GEOMETRY_H

#include <stdbool.h>
#include <xcb/xcb.h>

/**
 * @brief returns true if the given point is inside the given rectangle
 *
 * @param p the point
 * @param r the rectangle
 * @return true if p is inside r
 */
bool is_inside(xcb_point_t p, xcb_rectangle_t r);

/**
 * @brief Returns true if rectangle a contains rectangle b
 *
 * @param a the outer rectangle
 * @param b the inner rectangle
 * @return true if a is inside b
 */
bool contains(xcb_rectangle_t a, xcb_rectangle_t b);

/**
 * @brief Calculate the area of a rectangle
 *
 * @param r the rectangle
 * @return unsigned int, the area of the given rectangle
 */
unsigned int area(xcb_rectangle_t r);

/**
 * @brief Distance between the `dir` edge of `r1` and the `opposite(dir)` edge of `r2`.
 *
 * @param r1 the first rectangle
 * @param r2 the second rectangle
 * @param dir the direction (north/west/south/east)
 * @return uint32_t, the distance between the edges
 */
uint32_t boundary_distance(xcb_rectangle_t r1, xcb_rectangle_t r2, direction_t dir);

/**
 * @brief Is `r2` on the `dir` side of `r1`?
 *
 * @param r1 the first rectangle
 * @param r2 the second rectangle
 * @param dir the direction (north/west/south/east)
 * @return true
 */
bool on_dir_side(xcb_rectangle_t r1, xcb_rectangle_t r2, direction_t dir);

/**
 * @brief Compare if two rectangles (a and b) are equal in size and position
 *
 * @param a rectangle a
 * @param b rectangle b
 * @return true if the two rectangles are equal
 */
bool rect_eq(xcb_rectangle_t a, xcb_rectangle_t b);

/**
 * @brief Compare the positions of two rectangles
 *
 * @param r1 the first rectangle
 * @param r2 the second rectangle
 * @return integer, 1 if r1 is above or to the right of r2, -1 if r1 is below or to the left of r2.
 * If the rectangles overlap, return the area difference
 */
int rect_cmp(xcb_rectangle_t r1, xcb_rectangle_t r2);

#endif
