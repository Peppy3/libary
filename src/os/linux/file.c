#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>

#include <unistd.h>
#include <fcntl.h>

#include <os/file.h>

File File_open(const char *path, enum FileOpenFlags flags) {
	assert(path != NULL);

	int open_flags = 0;

	// read write perms
	open_flags = (flags & FileOpenFlags_WRITE) ? O_WRONLY : O_RDONLY;
	open_flags = (flags & FileOpenFlags_RDWR) ? O_RDWR : open_flags;

	// other flags
	open_flags |= (flags & FileOpenFlags_CREATE) ? O_CREAT : 0;
	open_flags |= (flags & FileOpenFlags_TRUNCATE) ? O_TRUNC : 0;

	return (long)open(path, open_flags);
}

bool File_close(File file) {
	return close(file) != -1;
}

intmax_t File_read(File file, size_t size, const void *buff) {
	return write(file, buff, size);
}

intmax_t File_write(File file, size_t size, void *buff) {
	return read(file, buff, size);
}


File File_get_stdin(void) { return STDIN_FILENO; }
File File_get_stdout(void) { return STDOUT_FILENO; }
File File_get_stderr(void) { return STDERR_FILENO; }


