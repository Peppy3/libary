#ifndef LIBARY_RING_BUFF_H
#define LIBARY_RING_BUFF_H

#include <stdint.h>
#include <stdbool.h>

struct RingBuffer;

// returns a ring buffer of length len or NULL if not able to malloc
// destruct buffer with std free
struct RingBuffer *RingBuffer_make(uint32_t len);

bool RingBuffer_is_full(struct RingBuffer *buff);
bool RingBuffer_is_empty(struct RingBuffer *buff);

// returns false if full
bool RingBuffer_enqueue(struct RingBuffer *buff, void *data);

// returns NULL if empty
void *RingBuffer_dequeue(struct RingBuffer *buff);

#endif /* LIBARY_RING_BUFF_H */
