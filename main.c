#include "kek.h"

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv", 53940, 7);
	print_mat(diamonds);
	// vec x = runif(100, 0, 1);print_vec(x);

	mat z = mat_multiply(mat_transpose(diamonds), diamonds);
	print_mat(z);
}
