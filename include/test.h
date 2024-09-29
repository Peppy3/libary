#ifndef LIBARY_TEST_H
#define LIBARY_TEST_H

/* 
 * test.h:
 *
 * This header file can be a bit confusing if you are not used to macros.
 * To write a test, just declare a TestCase function which takes a pointer
 * argument. The library will cast the funciton to the right type for you.
 * You have to make a TestRunner block and run the tests with the Test_run_test
 * macro.
 */

#include <stddef.h>
#include <stdbool.h>

// all cases that result in true are considered successfull
typedef bool (*TestFunc)(void*);

void __libary_Test_setup(int argc, char **argv);
void __libary_Test_shutdown(void);

#define TestRunner \
int __libary_Test_main(void);\
int main(int argc, char **argv) {\
	__libary_Test_setup(argc, argv);\
	int err = __libary_Test_main();\
	__libary_Test_shutdown();\
	return err;\
} \
int __libary_Test_main(void)


bool __libary_Test_run_test(TestFunc test_case, void *arg, char *name);
#define Test_run_test(test_case, arg) \
	__libary_Test_run_test((TestFunc)test_case, arg, #test_case)

bool __libary_Test_run_group(TestFunc test_case, void *arg, char *name);
#define Test_run_group(test_case, arg) \
	__libary_Test_run_group((TestFunc)test_case, arg, #test_case)

void Test_mem_err(void);

#endif /* LIBARY_TEST_H */
