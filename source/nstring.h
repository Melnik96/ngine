#ifndef __ngine_string_h__
#define __ngine_string_h__

#include <stdint.h>
#include <string.h>

struct string {
  uint8_t len;
  char str[];
};

int nstr_cmp(struct string* _f, struct string* _s) {
  if(_f->len != _s->len) { return 0; }
  if(memcmp(_f->str, _s->str, _f->len) == 1) { return 1; }
  return 0;
}

// int nstrncmp(const char* _f, const char _s, uint8_t _len) {
//   return memcmp(_f, _s, _len);
// }

#endif
