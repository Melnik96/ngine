#include "serialize.h"

struct a_struct {
  int f;
  int s;
};

struct some_struct {
  int f;
  int s;
  int t;
  struct a_struct* c;
};

sfunc_begin(a_struct,)
  sattr(f)
  sattr(s)
sfunc_end

sfunc_begin(some_struct,)
  sattr(f)
  sattr(s)
  sattr(t)
  sstruct_ptr(c, a_struct,)
sfunc_end
