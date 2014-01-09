#include <string.h>

#include "string.h"
#include "serialize.h"

#include "sfuncs.h"

int main() {
  struct string* str = malloc(sizeof(struct string));
  
  str->str = "char_ptr will be serialized";
  str->alloc = str->len = strlen("char_ptr will be serialized")+1;
  
  printf("str->str = %s\n"
	 "str->len = %i\n", str->str, str->len);
  
  struct buffer* str_buf = serialize(str, string,);
  
  printf("str_buf->size = %i\n"
	 "str_buf->data = %s\n", str_buf->size, str_buf->data);
  
  FILE* f = fopen("./sdata", "w");
  fwrite(str_buf->data, str_buf->size, 1, f);
  fclose(f);
  
  struct string* dstr = deserialize(str_buf->data, string,);
  
  printf("dstr->str = %s\n"
	 "dstr->len = %i\n", dstr->str, dstr->len);
}
