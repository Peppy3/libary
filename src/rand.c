#include <stddef.h>
#include <stdint.h>

#ifdef __STDC_NO_THREADS__
#error No threads.h pressent!
#else
#include <threads.h>
#endif

#include <stdlib.h>
#include <math.h>

static thread_local long int rand_val = 0;

// pcg pseudo rand
void Libary_srand(int seed) {
	rand_val = seed * 1664525u + 1013904223u;
}

// pcg pseudo rand
int Libary_rand(void) {
	long int state = rand_val * 747796405u + 2891336453u;
	rand_val = state;

	int word = ((state >> ((state >> 28u) + 4u)) ^ state) * 277803737u;
	return (word >> 22u) ^ word;
}

float Libary_random_float(void) {
	return Libary_rand() / ((float)INT32_MAX + 1.0f);
}

float Libary_random_float_min_max(float min, float max) {
	return min + (max - min) * Libary_random_float();
}

union BitCast {
	int32_t i;
	float f;
};

// initializes the buffer with random floats from 0.0f to 1.0f
// returns the passed in pointer to buff
float *Libary_random_float_buff(float *buff, size_t count) {

	for (size_t i = 0; i < count; i++) {
		// bit cast is faster than doing a int to float conversion
		// hex number is for normalizing the float
		union BitCast num = {.i = (Libary_rand() & 0xbf7fffff)};
		buff[i] = num.f;
	}
	
	return buff;
}

