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

#ifndef SYS_INFO_H
#define SYS_INFO_H

#include "stdint.h"

struct sys_info {
  // OS
  // CPU
  uint16_t cpu_num_cores;
  
  // GPU & OpenGL
  uint16_t gl_ver_major;
  uint16_t gl_ver_minor;
  // Sound
};

#endif // SYS_INFO_H
