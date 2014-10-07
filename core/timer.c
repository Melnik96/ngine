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

#include <sys/time.h>
#include <malloc.h>

#include "timer.h"

struct ngine_timer {
  double last_time_d;
  struct timeval cur_time;
  double cur_time_d;
};

struct ngine_timer* ngine_timer_create() {
  struct ngine_timer* new_timer = malloc(sizeof(struct ngine_timer));
  return new_timer;
}

void ngine_timer_delete(struct ngine_timer* _tim) {
  free(_tim);
}

void ngine_timer_start(struct ngine_timer* _tim) {
  struct timeval last_time;
  gettimeofday(&last_time, NULL);
  _tim->last_time_d = (double)last_time.tv_sec+(double)last_time.tv_usec/1000000.0;
}

double ngine_timer_elapsed(struct ngine_timer* _tim) {
  gettimeofday(&_tim->cur_time, NULL);
  _tim->cur_time_d = (double)_tim->cur_time.tv_sec+(double)_tim->cur_time.tv_usec/1000000.0;
  
  double diff = _tim->cur_time_d - _tim->last_time_d;
  
  _tim->last_time_d = _tim->cur_time_d;
  
  return diff;
}
