#include <malloc.h>
#include <stdio.h>

#include "a_serialize.h"

int main() {
//   for(uint32_t i = 0; i != 10000; ++i) {
  struct b* obj_b = calloc(1, sizeof(struct b));
  obj_b->f = 72;
  obj_b->s = 86;
  
  struct a* obj_a = calloc(1, sizeof(struct a));
  obj_a->f = 42;
  obj_a->s = 34;
  obj_a->t = obj_b;
  
  struct buffer* buf = serialize(obj_a, a,);
  
  FILE* f = fopen("sdata", "w");
  if(f != 0) {
    fwrite(buf->data, buf->size, 1, f);
    printf("sdata writen %i\n", buf->size);
  }
  fclose(f);
  
  struct a* des_a = deserialize(buf->data, a,);
  
  printf("des_a->f = %i\n"
	 "des_a->s = %i\n"
	 "des_a->t = %x\n\n"
	 "des_a->f = %i\n"
	 "des_a->s = %i\n", des_a->f, des_a->s, des_a->t,
			    des_a->t->f, des_a->t->s);
  
  free(buf->data);
  free(buf);
//   }
}
