#include "kek.h"
#include <stdio.h>
#include <threads.h>

u64 xoshiro256starstar(void);
void xoshiro256starstarjump(void);

#define NUM_THREADS 12

int run(void *arg) {
	(void) arg;
	vec x = runif(1e8, 0, 1);
	printf("%lf\n", x.x[0]);
	vec_free(x);
	return 0;
}

int main(void) {
	thrd_t t[NUM_THREADS];
	for (u64 i = 0; i < NUM_THREADS; i++) {
		thrd_create(&t[i], run, NULL);
		xoshiro256starstarjump();
	}
	for (u64 i = 0; i < NUM_THREADS; i++) {
		thrd_join(t[i], NULL);
	}
}
