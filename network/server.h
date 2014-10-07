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

#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>

typedef int(*event_handler_t)(int _sock);

struct ngine_server_event {
  uint32_t 		id;
  event_handler_t 	handler;
};

struct ngine_server {
  int 				base_sock;
  uint32_t 			num_events;
  struct ngine_server_event* 	events;
  char 				stop;
};

struct ngine_server* 	ngine_server_create(int _port);
void 			ngine_server_delete(struct ngine_server* _self);
void 			ngine_server_start(struct ngine_server* _self);
void 			ngine_server_stop(struct ngine_server* _self);
void 			ngine_server_add_handler(struct ngine_server* _self, uint32_t _id, event_handler_t _accept_handler);
void 			ngine_server_remove_handler(struct ngine_server* _self, uint32_t _id);

#endif // SERVER_H
