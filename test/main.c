#include <stdbool.h>

#include <test.h>

#include "ring_buff.c"
#include "arena.c"

#include "os/memory.c"

TestRunner {
	Test_run_group(ring_buffer, NULL);
	Test_run_group(arena, NULL);
	Test_run_group(os_memory, NULL);
	return 0;
}

