#include "kek.h"

int main(void) {
	mat d = read_mat("data/diamonds.csv");
	print(d);
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
