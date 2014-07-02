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

enum ngine_platform {
  NGINE_PLATFORM_AUTO = 0,
  NGINE_PLATFORM_WAYLAND,
  NGINE_PLATFORM_X,
  NGINE_PLATFORM_ANDROID,
  NGINE_PLATFORM_WINDOWS,
  NGINE_PLATFORM_DRM
};

struct ngine_iohand {
  enum ngine_platform platform;
};

struct ngine_iohand* ngine_iohand_create(enum ngine_platform _platform);

#endif // IOHAND_H
