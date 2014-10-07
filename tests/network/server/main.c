#include <sys/socket.h>

#include "network/server.h"

struct client_info {
  uint32_t id;
  uint32_t level;
};

int close_conn_cb(int _sock) {
  return 1;
}

int allow_conn_cb(int _sock) {
  struct client_info* cinf = malloc(sizeof(struct client_info));
  
  recv(_sock, cinf, sizeof(struct client_info), 0);
  printf("client info\n  id: %i\n  level: %i\n", cinf->id, cinf->level);
  
  char allow = 1;
  send(_sock, &allow, sizeof(char), 0);
  
  return 1;
}

int main(void) {
  struct ngine_server* serv = ngine_server_create(4041);
  
  ngine_server_add_handler(serv, 'q', close_conn_cb);
  ngine_server_add_handler(serv, 1, allow_conn_cb);
  
  ngine_server_start(serv);
  ngine_server_delete(serv);
}
