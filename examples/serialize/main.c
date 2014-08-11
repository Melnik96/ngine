#include "serialize.h"

#include "simpl.h"

int main() {
  struct a_struct* a = &(struct a_struct){4,5};
  struct some_struct* s = &(struct some_struct){1,2,3,a};
  struct buffer* buf = serialize(s, some_struct,);
  FILE* f = fopen("sdata", "w+");
  if(f != 0) {
    fwrite(buf->data, buf->size, 1, f);
    printf("sdata writen\n");
  }
  fclose(f);
  return 0;
}
