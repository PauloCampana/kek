#include "kek.h"
#include <stdio.h>

int main(void) {

	vec x = vec_new(SIGNED, 1e7);
	vec_fill(x, 0);
	print_vec(x);
	printf("%llu\n", any(x));

	// write_vec(x, "data/x.csv");

	// df iris = read_df("data/storms.csv", 19066, 10, "suuuuffsuu");
	// print_df(iris);
}
