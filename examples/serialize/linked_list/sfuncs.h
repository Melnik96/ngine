#include "serialize.h"
#include "serialize/string.h"
#include "tool.h"

sfunc(tool,)
  struct tool* _t;
  list_for_each(_t, s, link) {
    sstruct_ptr()
  }
  sstruct_ptr(name, string,)
  sstruct_ptr(type, string,)
  sint32(size)
funcs

dsfunc(tool,)
//   dsstruct(link)
  dsstruct_ptr(name, string,)
  dsstruct_ptr(type, string,)
  dsint32(size)
funcds
