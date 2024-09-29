#include <stddef.h>
#include <stdbool.h>

#include <string.h>

#include <test.h>

#include <arena.h>

bool arena_zero_size(void *state) {
	struct Arena *arena = Arena_new(0);
	
	if (arena != NULL) {
		Arena_destroy(arena);
	}
	
	return arena == NULL;
}


#define FIB_LEN 8
bool arena_can_hold_data(void *state) {
	static const int fib_correct[FIB_LEN] = {1, 1, 2, 3, 5, 8, 13};

	// assume the arena can hold FIB_LEN integers
	struct Arena *arena = Arena_new(sizeof(int) * FIB_LEN);
	
	if (arena == NULL) {
		Test_mem_err();
	}
	
	// fibonacci sequence
	int *x = Arena_alloc(arena, sizeof(int) * 2);
	x[0] = 1;
	x[1] = 1;
	
	for (size_t i = 2; i < FIB_LEN; i++) {
		int *x = Arena_alloc(arena, sizeof(int));
		*x = ((int*)arena)[i - 1] + ((int*)arena)[i - 2];
	}

	bool res = memcmp(arena, fib_correct, FIB_LEN) == 0;
	
	Arena_destroy(arena);

	return res;
}
#undef FIB_LEN

#define ARENA_LEN 67
bool arena_can_reset(void *state) {
	const char str[ARENA_LEN] = "This is a test string :3\n";
	
	struct Arena *arena = Arena_new(ARENA_LEN);

	char *foo = Arena_alloc(arena, ARENA_LEN);
	if (foo == NULL) {
		Test_mem_err();
	}
	
	strncpy(foo, str, ARENA_LEN);

	Arena_reset(arena);

	bool res = strncmp(str, foo, ARENA_LEN) != 0;
	
	Arena_destroy(arena);
	return res;
	
}
#undef ARENA_LEN

bool arena(void *state) {
	
	Test_run_test(arena_zero_size, NULL);
	Test_run_test(arena_can_hold_data, NULL);
	Test_run_test(arena_can_reset, NULL);

	return true;
}

