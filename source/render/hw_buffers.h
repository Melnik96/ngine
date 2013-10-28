#include <stdint.h>

struct hw_buffers {
  uint32_t vao;
  uint32_t vertex;
  uint32_t index;
};

struct hw_buffers* alloc_hw_bufs();

uint32_t hw_create_vao();
void hw_bind_vao(uint32_t );
void hw_unbind_vao();
