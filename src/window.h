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

#ifndef BSPWM_WINDOW_H
#define BSPWM_WINDOW_H

#include <stdarg.h>
#include <xcb/xcb.h>
#include <xcb/xcb_event.h>
#include <xcb/xcb_icccm.h>
#include "types.h"

void schedule_window(xcb_window_t win);
bool manage_window(xcb_window_t win, rule_consequence_t *csq, int fd);
void set_window_state(xcb_window_t win, xcb_icccm_wm_state_t state);
void unmanage_window(xcb_window_t win);
bool is_presel_window(xcb_window_t win);
void initialize_presel_feedback(node_t *n);
void draw_presel_feedback(monitor_t *m, desktop_t *d, node_t *n);
void refresh_presel_feedbacks(monitor_t *m, desktop_t *d, node_t *n);

/**
 * @brief Recursively show all preselection feedbacks for the given node and its children
 *
 * @param m the monitor
 * @param d the desktop
 * @param n the node
 */
void show_presel_feedbacks(monitor_t *m, desktop_t *d, node_t *n);

/**
 * @brief Recursively hide all preselection feedbacks for the given node and its children
 *
 * @param m the monitor
 * @param d the desktop
 * @param n the node
 */
void hide_presel_feedbacks(monitor_t *m, desktop_t *d, node_t *n);
void update_colors(void);
void update_colors_in(node_t *n, desktop_t *d, monitor_t *m);
void draw_border(node_t *n, bool focused_node, bool focused_monitor);

/**
 * @brief Give a colored border to the given window
 *
 * @param win the window
 * @param border_color_pxl the border color
 */
void window_draw_border(xcb_window_t win, uint32_t border_color_pxl);
void adopt_orphans(void);


/**
 * @brief Get the border color, depending on if the node or monitor is focused
 *
 * @param focused_node true if the node is focused, else false
 * @param focused_monitor true if the monitor is focused, else false
 * @return uint32_t: the border color
 */
uint32_t get_border_color(bool focused_node, bool focused_monitor);
void initialize_floating_rectangle(node_t *n);
xcb_rectangle_t get_window_rectangle(node_t *n);
bool move_client(coordinates_t *loc, int dx, int dy);
bool resize_client(coordinates_t *loc, resize_handle_t rh, int dx, int dy, bool relative);
void apply_size_hints(client_t *c, uint16_t *width, uint16_t *height);
void query_pointer(xcb_window_t *win, xcb_point_t *pt);
void update_motion_recorder(void);
void enable_motion_recorder(xcb_window_t win);
void disable_motion_recorder(void);

/**
 * @brief Change the border width of a window
 *
 * @param win the window
 * @param bw the new border width
 */
void window_border_width(xcb_window_t win, uint32_t bw);

/**
 * @brief Move a window
 *
 * @param win the window
 * @param x the new x position of the top left corner
 * @param y the new y position of the top left corner
 */
void window_move(xcb_window_t win, int16_t x, int16_t y);

/**
 * @brief Resize a window
 *
 * @param win the window
 * @param w the new width
 * @param h the new height
 */
void window_resize(xcb_window_t win, uint16_t w, uint16_t h);

/**
 * @brief Move & resize the given window
 *
 * @param win the window
 * @param x the new x position of the top left corner
 * @param y the new y position of the top left corner
 * @param w the new width
 * @param h the new height
 */
void window_move_resize(xcb_window_t win, int16_t x, int16_t y, uint16_t w, uint16_t h);


/**
 * @brief TODO
 *
 * @param m
 * @param c
 */
void window_center(monitor_t *m, client_t *c);

/**
 * @brief Change the window stacking order
 *
 * @param w1
 * @param w2
 * @param mode The stacking mode
 */
void window_stack(xcb_window_t w1, xcb_window_t w2, uint32_t mode);

/**
 * @brief Stack w2 below w1
 *
 * @param w1
 * @param w2
 */
void window_above(xcb_window_t w1, xcb_window_t w2);

/**
 * @brief Stack w1 below w2
 *
 * @param w1
 * @param w2
 */
void window_below(xcb_window_t w1, xcb_window_t w2);

/**
 * @brief Move the window to the bottom of the stack
 *
 * @param win the window to lower
 */
void window_lower(xcb_window_t win);

/**
 * @brief Set the visibility for the given window
 *
 * @param win the window
 * @param visible true: set window visible, else invisible
 */
void window_set_visibility(xcb_window_t win, bool visible);

/**
 * @brief Set the given window's visiblity to false
 *
 * @param win the window
 */
void window_hide(xcb_window_t win);

/**
 * @brief Set the given window's visiblity to true
 *
 * @param win the window
 */
void window_show(xcb_window_t win);

/**
 * @brief Set the input focus to the currently focused node
 * (to prevent input focus stealing)
 *
 */
void update_input_focus(void);

/**
 * @brief Set the focus to the given node
 *
 * @param n The node to give focus to
 */
void set_input_focus(node_t *n);

/**
 * @brief Set the focus to root
 *
 */
void clear_input_focus(void);

/**
 * @brief Move the pointer to the center of the given rectangle
 *
 * @param r the rectangle to center the pointer in
 */
void center_pointer(xcb_rectangle_t r);

/**
 * @brief Get the atom by name
 *
 * @param name name of the atom
 * @param atom pointer to the xcb_atom_t object
 */
void get_atom(char *name, xcb_atom_t *atom);
void set_atom(xcb_window_t win, xcb_atom_t atom, uint32_t value);
void send_client_message(xcb_window_t win, xcb_atom_t property, xcb_atom_t value);
bool window_exists(xcb_window_t win);

#endif
