// #include "network/client.h"
// 
// struct client_info {
//   uint32_t id;
//   uint32_t level;
// };
// 
// int main(void) {
//   struct ngine_client* cli = ngine_client_create();
//   printf("query 1\n");
//   ngine_client_connect(cli, "127.0.0.1", 4041);
//   ngine_client_query(cli, 1);
//   struct client_info cinfo;
//   cinfo.id = 3215;
//   cinfo.level = 4;
//   
//   ngine_client_send(cli, &cinfo, sizeof(struct client_info));
//   
//   char allowd;
//   
//   ngine_client_recv(cli, &allowd, sizeof(char));
//   
//   if(allowd) {
//     printf("acces to server allowd\n");
//   } else {
//     printf("acces to server not allowd\n");
//   }
//   
//   ngine_client_end(cli);
//   ngine_client_disconnect(cli);
//   ngine_client_delete(cli);
// }
