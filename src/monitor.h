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

#ifndef BSPWM_MONITOR_H
#define BSPWM_MONITOR_H

#define DEFAULT_MON_NAME     "MONITOR"

/**
 * @brief Create a new monitor and return the pointer to it
 *
 * @param name the monitor name
 * @param rect the rectangle describing the monitor
 * @param id the monitor id. If XCB_NONE, an id will be generated
 * @return monitor_t* the pointer to the created monitor
 */
monitor_t *make_monitor(const char *name, xcb_rectangle_t *rect, uint32_t id);
void update_root(monitor_t *m, xcb_rectangle_t *rect);
void reorder_monitor(monitor_t *m);

/**
 * @brief Rename a monitor
 *
 * @param m the monitor
 * @param name the new name
 */
void rename_monitor(monitor_t *m, const char *name);

/**
 * @brief Get the monitor by its id
 *
 * @param id the id to look for
 * @return monitor_t* - the monitor, or NULL if not found
 */
monitor_t *find_monitor(uint32_t id);

/**
 * @brief Get the monitor by its randr id
 *
 * @param id the randr id
 * @return monitor_t* - the monitor, or NULL if not found
 */
monitor_t *get_monitor_by_randr_id(xcb_randr_output_t id);
void embrace_client(monitor_t *m, client_t *c);
void adapt_geometry(xcb_rectangle_t *rs, xcb_rectangle_t *rd, node_t *n);

/**
 * @brief Add a monitor to the monitor list
 *
 * @param m the monitor to add
 */
void add_monitor(monitor_t *m);

/**
 * @brief Unlink the given monitor from the linked list of monitors
 *
 * @param m the monitor to unlink
 */
void unlink_monitor(monitor_t *m);

/**
 * @brief Remove the monitor
 *
 * @param m the monitor to remove
 */
void remove_monitor(monitor_t *m);

/**
 * @brief Merge a monitor with another, transferring all desktops
 *
 * @param ms the source monitor
 * @param md the destination monitor
 */
void merge_monitors(monitor_t *ms, monitor_t *md);

/**
 * @brief Swap two monitors
 *
 * @param m1 the first monitor
 * @param m2 the second monitor
 * @return true if successful, else false
 */
bool swap_monitors(monitor_t *m1, monitor_t *m2);

/**
 * @brief TODO
 *
 * @param m the monitor
 * @param dir the cycle direction
 * @param sel
 * @return monitor_t*
 */
monitor_t *closest_monitor(monitor_t *m, cycle_dir_t dir, monitor_select_t *sel);

/**
 * @brief Check if a given point is inside the given monitor
 *
 * @param m the monitor
 * @param pt the point
 * @return true if pt is inside m, else false
 */
bool is_inside_monitor(monitor_t *m, xcb_point_t pt);

/**
 * @brief For a given point, return the monitor that point is in
 *
 * @param pt the point
 * @return monitor_t* the monitor, or NULL if not found
 */
monitor_t *monitor_from_point(xcb_point_t pt);

/**
 * @brief Return the monitor nearest to the center of the given client's floating rectangle
 *
 * @param c the client
 * @return monitor_t* the nearest monitor
 */
monitor_t *monitor_from_client(client_t *c);

/**
 * @brief Return the next monitor in the cycle
 *
 * @param m the monitor
 * @param dir
 * @param sel
 * @return monitor_t*
 */
monitor_t *nearest_monitor(monitor_t *m, direction_t dir, monitor_select_t *sel);
bool find_any_monitor(coordinates_t *ref, coordinates_t *dst, monitor_select_t *sel);
bool update_monitors(void);

#endif
