#include "kek.h"

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv");
	print_mat(diamonds);
	mat z = mat_multiply(mat_transpose(diamonds), diamonds);
	print_mat(z);
}
