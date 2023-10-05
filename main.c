#include "kek.h"

f64 mat_determinant2(mat x);

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv");
	print_mat(diamonds);

	mat y = mat_multiply(mat_transpose(diamonds), diamonds);
	print_mat(y);

	f64 d = mat_determinant(y);
	printf("\n%lg\n", d);
}
