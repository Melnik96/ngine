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

#include "client.h"

struct ngine_client* ngine_client_create() {
  struct ngine_client* new_client = malloc(sizeof(struct ngine_client));
  new_client->base_socket = socket(AF_INET , SOCK_STREAM , 0);
  if(new_client->base_socket == -1) {
    error("create client socket failed");
  } else {
    debug("create client socket");
  }
  
  return new_client;
}

void ngine_client_delete(struct ngine_client* _self) {
  close(_self->base_socket);
  free(_self);
}

void ngine_client_connect(struct ngine_client* _self, const char* _addr, int _port) {
  struct sockaddr_in server_addr;
  
  server_addr.sin_addr.s_addr = inet_addr(_addr);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(_port);
 
  if(connect(_self->base_socket , (struct sockaddr *)&server_addr , sizeof(server_addr)) < 0) {
    error("client connect failed");
  } else {
    debug("client connected to %s", _addr);
  }
}

void ngine_client_disconnect(struct ngine_client* _self) {

}

void ngine_client_query(struct ngine_client* _self, uint32_t _event_id) {
  // if mutex is free
  // block socket
  send(_self->base_socket, &_event_id, sizeof(uint32_t), 0);
}

void ngine_client_send(struct ngine_client* _self, void* _data, uint32_t _size) {
  send(_self->base_socket, _data, _size, 0);
}

void ngine_client_recv(struct ngine_client* _self, void* _data, uint32_t _size) {
  recv(_self->base_socket, _data, _self, 0);
}

void ngine_client_end(struct ngine_client* _self) {
  // unblock socket
}
