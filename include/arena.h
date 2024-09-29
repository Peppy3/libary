#ifndef LIBARY_ARENA_H
#define LIBARY_ARENA_H

#include <stddef.h>

//
// Arena allocator
//

struct Arena;

// returns NULL if not able to allocate arena or if size is zero
struct Arena *Arena_new(size_t size);

// destroys the arena
// the arena can not be uded after this point
void Arena_destroy(struct Arena *arena);

// allocates inside the arena
// returns NULL if it is unable to allocate a big enough space inside the arena
void *Arena_alloc(struct Arena *arena, size_t size);

// reset and set the arena space to all zeros
void Arena_reset(struct Arena *arena);

#endif /* LIBARY_ARENA_H */

