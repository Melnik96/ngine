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

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <malloc.h>

#include "core/log.h"
#include "network/socket.h"

#include "client.h"

struct ngine_client* ngine_client_create(struct ngine_socket* _sock) {
  struct ngine_client* new_client = malloc(sizeof(struct ngine_client));
  
  new_client->base_socket = _sock;
  
  return new_client;
}

void ngine_client_delete(struct ngine_client* _self) {
  close(_self->base_socket);
  free(_self);
}

void ngine_client_query(struct ngine_client* _self, uint32_t _event_id) {
  // if mutex is free
  // block socket
//   send(_self->base_socket->sock_fd, &_event_id, sizeof(uint32_t), 0);
  ngine_socket_send(_self->base_socket, &_event_id, sizeof(uint32_t));
}

void ngine_client_end(struct ngine_client* _self) {
  // unblock socket
}
