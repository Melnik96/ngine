#include <stdint.h>

struct hw_buffers {
  uint8_t vertex;
  uint8_t index;
  uint8_t uniform;
  uint8_t counter;
};

struct hw_buffers* alloc_hw_bufs();