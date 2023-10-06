#include "kek.h"

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv");
	// print_mat(diamonds);

	reg fit = reg_linear(diamonds, "price");
	print_mat(fit.coefficients);

	vec n = reg_residuals_norm(fit);
	print_vec(n);

	// vec yhat2 = mat_vec(yhat, "price");
	// // print_vec(yhat2);

	// vec resid = vec_new(yhat2.len);
	// for (u64 i = 0; i < resid.len; i++) {
	// 	resid.x[i] = y.x[0].x[i] - yhat2.x[i];
	// }

	// print_vec(resid);

	// printf("mean = %lg\n", mean(resid));
}
