#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>
#include <stdlib.h>

#define RING_BUFFER_ADD(i, len) (((i) + 1) % (len))

struct RingBuffer {
	unsigned int len;
	unsigned int front;
	unsigned int back;
	void *buff[];
};

struct RingBuffer *RingBuffer_make(uint32_t len) {
	struct RingBuffer *buff;

	if (len < 2) {
		return NULL;
	}

	buff = malloc(sizeof *buff + (sizeof(void*) * len));
	if (buff == NULL)
		return NULL;

	*buff = (struct RingBuffer){
		.len = len,
		.front = 0,
		.back = 0,
	};

	return buff;
}

bool RingBuffer_is_full(struct RingBuffer *buff) {
	return (buff->front + 1) % buff->len == buff->back;
}

bool RingBuffer_is_empty(struct RingBuffer *buff) {
	return buff->front == buff->back;
}

bool RingBuffer_enqueue(struct RingBuffer *buff, void *data) {
	uint32_t next_front = RING_BUFFER_ADD(buff->front, buff->len);

	if (next_front == buff->back) {
		return false;
	}

	buff->buff[buff->front] = data;
	buff->front = next_front;

	return true;
}

void *RingBuffer_dequeue(struct RingBuffer *buff) {
	uint32_t back = buff->back;
	if (buff->front == back) {
		return NULL;
	}

	void *data = buff->buff[back];
	buff->buff[back] = NULL;
	buff->back = RING_BUFFER_ADD(back, buff->len);

	return data;
}

