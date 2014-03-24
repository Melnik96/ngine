#include <sys/socket.h>

#include "serialize.h"
#include "sc_obj.h"

#include "server.h"

void server_update_scene(scene* _scene) {
  send("get obj data");
  void* sdata = recv("obj data");
  struct sc_obj* updated_obj = deserialize(sdata, sc_obj, marshal);
  //TODO deserialize to exiting object e.g. deserialize(updated_obj, sdata, sc_obj, marshal)
  //					or demarshal(updated_obj, sdata, sc_obj, mod)
}
