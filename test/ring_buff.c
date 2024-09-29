#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>

#include <test.h>

#include <ring_buff.h>

bool ring_buffer_zero_size(void *state) {
	// should return NULL
	struct RingBuffer *buff = RingBuffer_make(0);

	if (buff != NULL) {
		free(buff);
	}

	return buff == NULL;
}

bool ring_buffer_size_of_one(void *state) {
	struct RingBuffer *buff = RingBuffer_make(1);

	if (buff != NULL) {
		free(buff);
	}

	return true;

}

#define BUFF_LEN 7
bool ring_buffer_basic_setup(struct RingBuffer **buff) {
	struct RingBuffer *ret_buff;
	ret_buff = RingBuffer_make(BUFF_LEN);
	*buff = ret_buff;
	return ret_buff != NULL;
}

bool ring_buffer_is_empty(struct RingBuffer **buff) {
	return RingBuffer_is_empty(*buff) == true;
}

bool ring_buffer_can_hold_ptr(struct RingBuffer **buff) {
	void *foo = (void *)0xFEEDBEEF;

	// assume buffer is not full
	RingBuffer_enqueue(*buff, foo);

	void *foo_cpy = RingBuffer_dequeue(*buff);

	return foo == foo_cpy;
}

bool ring_buffer_dequeue_empty(struct RingBuffer **buff) {
	return RingBuffer_dequeue(*buff) == NULL;
}

bool ring_buffer_is_full(struct RingBuffer **buff) {
	void *foo[BUFF_LEN];

	for (size_t i = 0; i < BUFF_LEN; i++) {
		foo[i] = (void*)i;
		if (RingBuffer_enqueue(*buff, foo[i])) {
			return true;
		}
	}
	
	// We don't need to worry about taking everything out of the buffer

	return RingBuffer_is_full(*buff);
}
#undef BUFF_LEN

bool ring_buffer_enqueue_full(struct RingBuffer **buff) {
	void *foo = (void *)0xDEADBEEF;
	
	bool err = RingBuffer_enqueue(*buff, foo);
	return err == true;
}

#define NUM_PUSHES 17
bool ring_buffer_can_loop(void *state) {
	struct RingBuffer *buff = RingBuffer_make(5);

	if (buff == NULL) {
		Test_mem_err();
	}

	for (size_t i = 0; i < NUM_PUSHES; i++) {
		void *foo = (void *)i + 1;
	
		bool success = RingBuffer_enqueue(buff, foo);
	
		if (!success) {
			free(buff);
			return false;
		}
		
		void *foo_cpy = RingBuffer_dequeue(buff);
		
		if (foo_cpy == NULL || foo != foo_cpy) {
			free(buff);
			return false;
		}
	}
	return true;
}
#undef NUM_PUSHES

bool ring_buffer(void *state) {

	Test_run_test(ring_buffer_zero_size, NULL);
	Test_run_test(ring_buffer_size_of_one, NULL);

	{
		struct RingBuffer *buff = NULL;

		Test_run_test(ring_buffer_basic_setup, &buff);

		if (buff == NULL) {
			Test_mem_err();
		}
		
		Test_run_test(ring_buffer_is_empty, &buff);
		Test_run_test(ring_buffer_can_hold_ptr, &buff);

		Test_run_test(ring_buffer_dequeue_empty, &buff);
		
		Test_run_test(ring_buffer_is_full, &buff);
		
		Test_run_test(ring_buffer_enqueue_full, &buff);

		free(buff);
	}
	
	Test_run_test(ring_buffer_can_loop, NULL);

	return true;
}


