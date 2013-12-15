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

#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#include "log.h"

#include "net.h"

void rconsole_handler(void *socket_desc);

void rconsole_init() {
  debug("init remote console");
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0) { warning("filed create socket"); return; }
  
  struct sockaddr_in sc_in;
  memset(&sc_in, 0, sizeof(struct sockaddr_in));
  sc_in.sin_addr.s_addr = INADDR_ANY;
  sc_in.sin_port = htons(7072);
  sc_in.sin_family = AF_INET;
  
  if(bind(sock, (struct sockaddr *)&sc_in, sizeof(sc_in)) < 0) {
    warning("filed bind socket");
    return;
  }
  
  int lerror = listen(sock, 5);
  if(lerror == -1) { warning("filed listen"); }
  
  struct sockaddr cli_addr;
  int newsockfd = 0;
  while((newsockfd = accept(sock, &cli_addr, sizeof(struct sockaddr)))) {
    if(newsockfd == -1) { continue; }
    debug("remote console connection accepted");

    pthread_t thread;
    int* cur_sock = malloc(sizeof(int));
    *cur_sock = newsockfd;

    if(pthread_create(&thread, NULL, rconsole_handler, (void*)cur_sock) < 0) {
      warning("could not create thread");
      return 1;
    }

    //Now join the thread , so that we dont terminate before the thread
    //pthread_join( sniffer_thread , NULL);
    debug("handler assigned");
  }
}

void rconsole_handler(void *socket_desc) {
  debug("");
  //Get the socket descriptor
  int sock = *(int*)socket_desc;
  int read_size;
  char* message , client_message[2000];

  //Send some messages to the client
  message = "Greetings! I am your connection handler\n";
  write(sock , message , strlen(message));

  message = "Now type something and i shall repeat what you type \n";
  write(sock , message , strlen(message));

  //Receive a message from client
  while((read_size = recv(sock , client_message , 2000 , 0)) > 0) {
    //Send the message back to client
    write(sock , client_message , strlen(client_message));
  }

  if(read_size == 0) {
    debug("Client disconnected");
    fflush(stdout);
  }
  else if(read_size == -1) {
    warning("recv failed");
  }

  //Free the socket pointer
  free(socket_desc);
}
