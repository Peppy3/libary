#include <stdbool.h>

#include <test.h>

#include "ring_buff.c"
#include "arena.c"

TestRunner {
	Test_run_group(ring_buffer, NULL);
	Test_run_group(arena, NULL);
	return 0;
}

