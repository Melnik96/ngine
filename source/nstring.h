#ifndef __ngine_string_h__
#define __ngine_string_h__

#include <stdint.h>
#include <string.h>

struct string {
  uint8_t len;
  char str[];
};

typedef struct string string;

struct string* nstr(const char* _cstr) {
  struct string* str = malloc(sizeof(struct string));
  str->str = _cstr;
  str->len = strlen(_cstr);
//   str->alloc = str->len + 1;
  return str;
}

int nstrcmp(struct string* _f, struct string* _s) {
  if(_f->len != _s->len) { return 0; }
  return memcmp(_f->str, _s->str, _f->len);
}

nstrcat(struct string* _d, ...) {}

// int nstrncmp(const char* _f, const char _s, uint8_t _len) {
//   return memcmp(_f, _s, _len);
// }

#endif
