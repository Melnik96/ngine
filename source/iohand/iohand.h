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

#ifndef IOHAND_H
#define IOHAND_H

#include <stdint.h>

enum ngine_platform {
  NGINE_PLATFORM_AUTO = 0,
  NGINE_PLATFORM_WAYLAND,
  NGINE_PLATFORM_X,
  NGINE_PLATFORM_DRM,
  NGINE_PLATFORM_ANDROID,
  NGINE_PLATFORM_WINDOWS
};

struct ngine_platform_handler {
  struct window {
    void(*create)();
    void(*delete)();
    void(*make_ctx_cur)();
    void(*set_input_handler)();
  } window;
};

struct ngine_iohand {
  uint32_t platform;
  struct ngine_platforn_handler* platform_handler; 
};

struct ngine_iohand* ngine_iohand_create(uint32_t _platform);

#endif // IOHAND_H
