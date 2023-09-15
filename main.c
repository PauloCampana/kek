#include "kek.h"

vec vec_add(vec x, vec y);

int main(void) {
	vec x = runif(1e6, 0, 1);
	print_vec(x);
}
