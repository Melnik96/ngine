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
// #define __USE_POSIX
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdlib.h>
#include <errno.h>

#include "core/log.h"

#include "socket.h"

struct ngine_socket* ngine_socket_create() {
  struct ngine_socket* new_socket = calloc(1, sizeof(struct ngine_socket));
  
  new_socket->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(new_socket->sock_fd == -1) {
    error("create socket failed");
  } else {
    debug("create socket");
  }
  
  return new_socket;
}

void ngine_socket_delete(struct ngine_socket* _self) {
  close(_self->sock_fd);
  free(_self);
}

void ngine_socket_connect(struct ngine_socket* _self, const char* _addr, int _port) {
  struct addrinfo* addr_info = 0;
  char s_port[6];
  sprintf(s_port, "%i", _port);
  
  getaddrinfo(_addr, s_port, 0, &addr_info);
  addr_info->ai_addr->sa_family = AF_INET;
  
  if(connect(_self->sock_fd, addr_info->ai_addr, addr_info->ai_addrlen) == -1) {
    error("socket connect failed; errno = %i", errno);
  } else {
    debug("socket connected to %s", _addr);
  }
}

void ngine_socket_listen(struct ngine_socket* _self, int _port) {
  struct sockaddr_in serv_addr;
  
  memset((char *)&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(_port);
 
  
  if(bind(_self->sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("bind socket failed");
  } else {
    debug("bind socket");
  }
  
  if(listen(_self->sock_fd, 32) == -1) {
    error("socket start listen failed");
  } else {
    debug("socket start listen");
  }
}

struct ngine_socket* ngine_socket_accept(struct ngine_socket* _self) {
  struct sockaddr_in cli_addr;
  socklen_t cli_addr_len = sizeof(cli_addr);
  
  struct ngine_socket* accept_sock = malloc(sizeof(uint32_t));
  
  accept_sock->sock_fd = accept(_self->sock_fd, (struct sockaddr *) &cli_addr, &cli_addr_len);
  if(accept_sock->sock_fd == -1) {
    error("socket accept failed");
  }
  
  return accept_sock;
}

void ngine_socket_send(struct ngine_socket* _self, void* _data, uint32_t _size) {
  if(send(_self->sock_fd, _data, _size, 0) == -1) {
    error("socket send failed");
  }
}

void ngine_socket_recv(struct ngine_socket* _self, void* _data, uint32_t _size) {
  if(recv(_self->sock_fd, _data, _size, 0) == -1) {
    error("socket recv failed");
  }
}
