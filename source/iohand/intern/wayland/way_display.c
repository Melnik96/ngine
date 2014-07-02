/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "log.h"

#include "way_display.h"

struct ngine_way_display* ngine_way_display_create(const char* _dyp_name) {
  struct ngine_way_display* new_way_display = NULL;
  
  new_way_display->display = wl_display_connect(_dyp_name);
  if(!new_way_display->display) {
    error("iohand: cannot conect to Wayland server '%s'", _dyp_name);
  }
  
  new_way_display->registry = wl_display_get_registry(new_way_display->display);
  wl_registry_add_listener(new_way_display->registry, &registry_listener, new_way_display);

  wl_display_dispatch(new_way_display->display);

  // init EGL display
  
  
	init_egl(&display, &window);
	create_surface(&window);
	init_gl(&window);

	display.cursor_surface = wl_compositor_create_surface(display.compositor);

	sigint.sa_handler = signal_int;
	sigemptyset(&sigint.sa_mask);
	sigint.sa_flags = SA_RESETHAND;
	sigaction(SIGINT, &sigint, NULL);

	/* The mainloop here is a little subtle.  Redrawing will cause
	 * EGL to read events so we can just call
	 * wl_display_dispatch_pending() to handle any events that got
	 * queued up as a side effect. */
	while (running && ret != -1) {
		wl_display_dispatch_pending(display.display);
		redraw(&window, NULL, 0);
	}

}

void ngine_way_display_delete(struct ngine_way_display* _self) {
  debug("iohend: disconnect Weyland");

  destroy_surface(&window);
  fini_egl(&display);

  wl_surface_destroy(display.cursor_surface);
  if(display.cursor_theme)
    wl_cursor_theme_destroy(display.cursor_theme);

  if (display.shell) xdg_shell_destroy(display.shell);

  if (display.compositor)
	wl_compositor_destroy(display.compositor);

  wl_registry_destroy(display.registry);
  wl_display_flush(display.display);
  wl_display_disconnect(display.display);
}
