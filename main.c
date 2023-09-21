#include "kek.h"

int main(void) {
	for (f64 i = 0; i < 1; i += 0.01) {
		f64 x = qlnorm(i, 0, 1);
		printf("q(%.2lf) = %lg\n", i, x);
	}
	f64 x = qlnorm(1, 0, 1);
	printf("q(%.2lf) = %lg\n", 1.0, x);

}
