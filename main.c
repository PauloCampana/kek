#include "kek.h"

vec rnorm2(u64 n, f64 mean, f64 sd);
int main(void) {
	vec x = rnorm2(1e6, 0, 1);
	print(x);
}
	// stopifnot

	// mat_sort
	// mat_rbind
	// mat_cbind

	// vec_set_union      A u B
	// vec_set_intersect  A n B
	// vec_set_difference A - B
	// vec_set_in         A c B
	// vec_set_equal      A = B

	// which should determine which indices are not 0,
	// no operation bullshit
