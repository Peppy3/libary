#ifndef LIBARY_RAND_H
#define LIBARY_RAND_H

// pcg pseudo random generator (faster than std rand)
// these are pretty self explanatory
void Libary_srand(int seed);
int Libary_rand(void);

// uses the library's rand funcition
float Libary_random_float(void);
float Libary_random_float_min_max(float min, float max);

// initializes the buffer with random floats from 0.0f to 1.0f
// returns the passed in pointer to buff
float *Libary_random_float_buff(float *buff, size_t count);

#endif /* LIBARY_RAND_H */
