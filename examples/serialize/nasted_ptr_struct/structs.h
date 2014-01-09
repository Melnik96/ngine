#include <stdint.h>

#ifndef __structs_H__
#define __structs_H__

struct b {
  int32_t f;
  int32_t s;
};

struct a {
  int32_t f;
  int32_t s;
  struct b* t;
};

#endif
