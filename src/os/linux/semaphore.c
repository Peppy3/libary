#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#include <stdatomic.h>

#include <stdlib.h>

#include <linux/futex.h>
#include <arena.h>

struct Semaphore {
	long max_count;
	uint32_t count;
};

struct Semaphore *Semaphore_create(long max_count) {
	struct Semaphore *sem;
	static_assert(atomic_is_lock_free(&sem->count));
	
	if (max_count <= 0) {
		return NULL;
	}

	sem = malloc(sizeof *sem);
	if (sem == NULL) {
		return NULL;
	}
	
	sem->max_count = max_count;
	sem->count = 0;

	return sem;
}

void Semaphore_post(struct Semaphore *sem) {
	// TODO:
}


