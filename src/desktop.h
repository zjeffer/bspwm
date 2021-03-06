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

#ifndef BSPWM_DESKTOP_H
#define BSPWM_DESKTOP_H

#define DEFAULT_DESK_NAME    "Desktop"

/**
 * @brief Activate the given desktop
 *
 * @param m the monitor
 * @param d the desktop
 * @return true if succesfull
 */
bool activate_desktop(monitor_t *m, desktop_t *d);

/**
 * @brief TODO: explain
 *
 * @param ref
 * @param dst
 * @param dir
 * @param sel
 * @return true
 * @return false
 */
bool find_closest_desktop(coordinates_t *ref, coordinates_t *dst, cycle_dir_t dir, desktop_select_t *sel);

/**
 * @brief TODO: explain
 *
 * @param ref
 * @param dst
 * @param sel
 * @return true
 * @return false
 */
bool find_any_desktop(coordinates_t *ref, coordinates_t *dst, desktop_select_t *sel);

/**
 * @brief Set the layout for the given desktop
 *
 * @param m the monitor
 * @param d the desktop
 * @param l the layout
 * @param user specify if the given layout is a user layout (TODO: is this correct? does it need more info?)
 * @return true if succesfull
 */
bool set_layout(monitor_t *m, desktop_t *d, layout_t l, bool user);

/**
 * @brief Update the preselection feedbacks for the given desktop
 *
 * @param m the monitor that contains the desktop
 * @param d the desktop to update
 */
void handle_presel_feedbacks(monitor_t *m, desktop_t *d);

/**
 * @brief Transfer the given desktop to a new monitor
 *
 * @param ms the source monitor
 * @param md the destination monitor
 * @param d the desktop to transfer
 * @param follow true if the new monitor must be active
 * @return true if succesfully transfered
 */
bool transfer_desktop(monitor_t *ms, monitor_t *md, desktop_t *d, bool follow);

/**
 * @brief Create a new desktop and return it
 *
 * @param name
 * @param id
 * @return desktop_t* - the new desktop
 */
desktop_t *make_desktop(const char *name, uint32_t id);

/**
 * @brief Rename the given desktop
 *
 * @param m the monitor
 * @param d the desktop
 * @param name the new name
 */
void rename_desktop(monitor_t *m, desktop_t *d, const char *name);

/**
 * @brief Add the desktop to the end of the desktop list of the given monitor
 *
 * @param m the monitor
 * @param d the desktop
 */
void insert_desktop(monitor_t *m, desktop_t *d);

/**
 * @brief Add a new desktop to the given monitor
 *
 * @param m the monitor
 * @param d the new desktop
 */
void add_desktop(monitor_t *m, desktop_t *d);

/**
 * @brief Find the desktop by id
 *
 * @param id the desktop id
 * @param m the monitor to search on
 * @return desktop_t* - the desktop, or NULL if not found
 */
desktop_t *find_desktop_in(uint32_t id, monitor_t *m);

/**
 * @brief Unlink the given desktop, updates the linked list
 *
 * @param m
 * @param d
 */
void unlink_desktop(monitor_t *m, desktop_t *d);

/**
 * @brief Remove the given desktop
 *
 * @param m the monitor
 * @param d the desktop
 */
void remove_desktop(monitor_t *m, desktop_t *d);

/**
 * @brief Merge two desktops, transferring all nodes from the source to the destination desktop
 *
 * @param ms The source monitor
 * @param ds The source desktop
 * @param md The destination monitor
 * @param dd The destination desktop
 */
void merge_desktops(monitor_t *ms, desktop_t *ds, monitor_t *md, desktop_t *dd);

/**
 * @brief Swap two desktops
 *
 * @param m1 the first monitor
 * @param d1 the first desktop
 * @param m2 the second monitor
 * @param d2 the second desktop
 * @param follow boolean, should the first or second desktop be focused/activated
 * @return true if succesfully swapped
 */
bool swap_desktops(monitor_t *m1, desktop_t *d1, monitor_t *m2, desktop_t *d2, bool follow);

/**
 * @brief Show the given desktop
 *
 * @param d the desktop
 */
void show_desktop(desktop_t *d);

/**
 * @brief Hide the given desktop
 *
 * @param d the desktop
 */
void hide_desktop(desktop_t *d);

/**
 * @brief Return true if a desktop has an urgent node
 *
 * @param d the desktop to query
 * @return true if the desktop has at least one urgent node
 */
bool is_urgent(desktop_t *d);

#endif
