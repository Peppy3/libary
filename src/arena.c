#include <stddef.h>

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <stdatomic.h>

struct Arena {
	size_t cap;
	atomic_size_t allocated;
};

struct Arena *Arena_new(size_t size) {
	struct Arena *arena;
	if (size == 0) {
		return NULL;
	}
	
	arena = malloc(sizeof *arena + size);
	if (arena == NULL) {
		return NULL;
	}

	*arena = (struct Arena) {
		.cap = size,
		.allocated = 0
	};
	
	// memset returns a void* so it will be infered to 
	// be a struct Arena* even though it's pointing to the data part
	return memset(arena + 1, 0, size);
}

void Arena_destroy(struct Arena *__arena) {
	struct Arena *arena = __arena -1;
	free(arena);
}

void *Arena_alloc(struct Arena *__arena, size_t size) {
	if (size == 0) {
		return NULL;
	}
	
	struct Arena *arena = __arena - 1;

	size_t old_alloced = arena->allocated;
	size_t new_alloced = old_alloced + size;

	if (new_alloced > arena->cap) {
		return NULL;
	}

	arena->allocated = new_alloced;

	return ((char *)__arena) + old_alloced;
}

void Arena_reset(struct Arena *__arena) {
	struct Arena *arena = __arena - 1;

	arena->allocated = 0;

	memset(__arena, 0, arena->cap);
}

