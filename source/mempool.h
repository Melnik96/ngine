#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

struct mempools {
  struct mempool* scene_object_pool;
  struct mempool* entity_pool;
  struct mempool* mesh_pool;
  struct mempool* dynlib_pool;
  struct mempool* camera_pool;
};
static mempools* mempools;

struct mempool {
  void* head;
  void* mem;
};

/* allocate a chunk from the pool. */
void* mempool_alloc(struct mempool* buf) {
//   if(!buf)
//     return NULL;

  if(!buf->head)
    return NULL; /* out of memory */

  uint8_t* currPtr = buf->head;
  buf->head = (*((uint8_t**)(buf->head)));
  return currPtr;
}


/* return a chunk to the pool. */
void mempool_free(struct mempool* buf, void* ptr) {
//   if(!buf || !ptr)
//     return;

  *((uint8_t**)ptr) = buf->head;
  buf->head = (uint8_t*)ptr;
  return;
}


/* initialise the pool header structure, and set all chunks in the pool as empty. */
void mempool_init(struct mempool* buf, uint8_t* mem, uint32_t size, uint32_t chunkSize) {
//   if(!buf || !mem || !size || !chunkSize)
//     return;

  const uint32_t chunkCount = (size / chunkSize) - 1;
  for(uint32_t chunkIndex = 0; chunkIndex < chunkCount; ++chunkIndex) {
    uint8_t* currChunk = mem + (chunkIndex * chunkSize);
    *((uint8_t**)currChunk) = currChunk + chunkSize;
  }

  *((uint8_t**)&mem[chunkCount * chunkSize]) = NULL; /* terminating NULL */
  buf->mem = buf->head = mem;
  return;
}

#endif
