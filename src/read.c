#include "../kek.h"

mat read_mat(s64 path, u64 nrow, u64 ncol) {
	vec *x = malloc(ncol * sizeof *x);
	s64 *names = malloc(ncol * sizeof *names);
	FILE *csv = fopen(path, "r");
	for (u64 j = 0; j < ncol; j++) {
		x[j].len = nrow;
		x[j].x = malloc(nrow * sizeof x[j].x);
		names[j] = malloc(64);
		u64 signal = fscanf(csv, "\n%[^,;\t\n],", names[j]);
		if (signal != 1) exit(1);
	}
	s64 buffer = malloc(64);
	for (u64 i = 0; i < nrow; i++) {
		for (u64 j = 0; j < ncol; j++) {
			u64 signal = fscanf(csv, "\n%[^,;\t\n],", buffer);
			if (signal != 1) exit(1);
			x[j].x[i] = strtod(buffer, NULL);
		}
	}
	fclose(csv);
	return (mat) {ncol, names, x};
}
