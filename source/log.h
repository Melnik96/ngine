/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  <copyright holder> <email>
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

#ifndef LOG_H
#define LOG_H

#include <stdio.h>

extern FILE* error_stream;
extern FILE* warning_stream;
extern FILE* debug_stream;

void(*on_error)(void);
void(*on_warning)(void);
void(*on_debug)(void);

#define error(MSG, ...) { printf("[ERROR] (%s:%s:%i) ", __FILE__, __func__, __LINE__); printf(MSG, ##__VA_ARGS__); printf("\n"); fflush(stdout); on_error(); }
#define warning(MSG, ...) { printf("[WARNING] (%s:%s:%i) ", __FILE__, __func__, __LINE__); printf(MSG, ##__VA_ARGS__); printf("\n"); fflush(stdout); on_warning(); }
#define debug(MSG, ...) { printf("[DEBUG] (%s:%s:%i) ", __FILE__, __func__, __LINE__); printf(MSG, ##__VA_ARGS__); printf("\n"); fflush(stdout); on_debug(); }

#endif // LOG_H
