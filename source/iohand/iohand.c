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

#include <stdlib.h>

// #include "intern/wayland/"
// #include "intern/x11/"
#include "intern/glfw/glfw_iohand.h"

#include "iohand.h"

#define USE_GLFW
/*
struct ngine_iohand* ngine_iohand_create(ngine_platform _platform) {
  struct ngine_iohand* new_iohand = NULL;
  
#ifdef !USE_GLFW
  new_iohand = ngine_glfw_iohand_create(_platform);
#else
  if(_platform == NGINE_PLATFORM_AUTO) {
    if(getenv("WAYLAND")) {
      new_iohand = ngine_way_iohand_create();
    } else if(getenv("DISPLAY")) {
      new_iohand = ngine_x11_iohand_create();
    }
  } else if(_platform == NGINE_PLATFORM_WAYLAND) {
    new_iohand = ngine_way_iohand_create();
  } else if(_platform == NGINE_PLATFORM_X) {
    new_iohand = ngine_x11_iohand_create();
  } else if(_platform == NGINE_PLATFORM_DRM) {
    new_iohand = ngine_drm_iohand_create();
  } else if(_platform == NGINE_PLATFORM_ANDROID) {
    new_iohand = ngine_android_iohand_create();
  } else if(_platform == NGINE_PLATFORM_WINDOWS) {
    new_iohand = ngine_win_iohand_create();
  }
#endif
}*/
