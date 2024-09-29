#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include <test.h>

#define ERROR "ERROR: "

struct TestState {
	char *curr_test;
	char *curr_group;
	
	uint32_t failiures;
	uint32_t sucesses;
	uint32_t num_tests;

	uint32_t total_tests;
	uint32_t total_fails;
} test_state;

void Test_mem_err(void) {
	char *curr_test = test_state.curr_test;

	fprintf(stderr, "%s\n" 
			ERROR "memory error. I can not recover from this\n", 
			(curr_test != NULL) ? curr_test : "(null)"
			);

	exit(1);
}

void __libary_Test_setup(int argc, char **argv) {
	test_state.curr_test = NULL;
	test_state.total_tests = 0;
	return;
}

void __libary_Test_shutdown(void) {
	printf(
		"Total numer of tests: %u\n"
		"Number of tests failed: %u\n",
		test_state.total_tests,
		test_state.total_fails
		);
	return;
}

bool __libary_Test_run_test(TestFunc test_case, void *arg, char *name) {
	assert(name != NULL);
	test_state.curr_test = name;
	test_state.num_tests += 1;
	test_state.total_tests += 1;
	
	bool err_state = test_case(arg);
	fflush(stdout);
	if (err_state == false) {
		fprintf(stdout, ERROR "%s retured %d\n", name, err_state);
		test_state.failiures += 1;
		test_state.total_fails += 1;
		return err_state;
	}

	fprintf(stdout, "\tSuccess: %s\n", name);
	test_state.sucesses += 1;
	return err_state;
}

bool __libary_Test_run_group(TestFunc test_group, void *arg, char *name) {
	test_state.curr_group = name;
	test_state.failiures = 0;
	test_state.sucesses = 0;
	test_state.num_tests = 0;

	fprintf(stdout, "Running: %s\n", name);
	bool err_state = test_group(arg);
	fflush(stdout);

	fprintf(stdout, 
			"\nResults for %s: \n"
			"Number of tests: %u\n"
			"Successes: %u\n"
			"Failiures: %u\n\n",
			name, 
			test_state.num_tests,
			test_state.sucesses, test_state.failiures
			);

	return err_state;
}

