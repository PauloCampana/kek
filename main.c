#include "kek.h"

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv", 53940, 7);
	// print_mat(diamonds);

	// mat z = mat_multiply(mat_transpose(diamonds), diamonds);
	mat z = mat_multiply(mat_transpose(diamonds), diamonds);
	print_mat(z);
}
