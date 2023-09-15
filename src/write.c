#include "../kek.h"

void write_vec(vec x, s64 path) {
	FILE *csv = fopen(path, "w");
	fprintf(csv, "col\n");
	for (u64 i = 0; i < x.len; i++) {
		fprintf(csv, "%.16lf\n", x.x[i]);
	}
	fclose(csv);
}
