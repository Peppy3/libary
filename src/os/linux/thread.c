#include <stddef.h>

#include <unistd.h>

int procs_online(void) {
	return sysconf(_SC_NPROCESSORS_ONLN);
}

