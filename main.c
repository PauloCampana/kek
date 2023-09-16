#include "kek.h"

int main(void) {
	for (u64 i = 0; i < 1e7; i++) {
		dt(3, 3);
	}

	printf("%.16lf\n", dt(3, 3));
}
