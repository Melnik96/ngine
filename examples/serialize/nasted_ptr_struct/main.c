#include <string.h>

#include "serialize.h"

#include "sfuncs.h"
#include "structs.h"

int main() {
  struct a* sa = malloc(sizeof(struct a));
  struct b* sb = malloc(sizeof(struct b));
  
  sa->f = 12;
  sa->s = 22;
  sa->t = sb;
  
  sb->f = 32;
  sb->s = 33;
  
  struct buffer* str_buf = serialize(sa, a,);
  
  printf("str_buf->size = %i\n"
	 "str_buf->data = %s\n", str_buf->size, str_buf->data);
  
  FILE* f = fopen("./sdata", "w");
  fwrite(str_buf->data, str_buf->size, 1, f);
  fclose(f);
  
  printf("begin deserialization\n");
  
  struct a* dsa = deserialize(str_buf->data, a,);
  
  printf("dsa.f = %i\n"
	 "dsa.s = %i\n"
	 "dsa.t = %x\n"
	 "dsa.t.f = %i\n"
	 "dsa.t.s = %i\n", dsa->f, dsa->s, dsa->t, dsa->t->f, dsa->t->f);
}
