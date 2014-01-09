#include "cntr/list.h"

#ifndef TOOL_H
#define TOOL_H

struct tool {
  struct list link;
  struct string* name;
  struct string* type;
  size_t size;
};

#endif
