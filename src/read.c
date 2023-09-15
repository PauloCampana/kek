#include "../kek.h"

df read_df(s64 path, u64 nrow, u64 ncol) {
	FILE *csv = fopen(path, "r");
	s64 *colnames = malloc(ncol * sizeof *colnames);
	vec *var = malloc(ncol * sizeof *var);

	for (u64 j = 0; j < ncol; j++) {
		var[j] = (vec) {nrow, malloc(nrow * sizeof var[j].x)};
		colnames[j] = malloc(64);
		u64 signal = fscanf(csv, "\n%[^,;\t\n],", colnames[j]);
		if (signal != 1) exit(1);
	}
	for (u64 i = 0; i < nrow; i++) {
		for (u64 j = 0; j < ncol; j++) {
			u64 signal = fscanf(csv, "%lf,", &var[j].x[i]);
			if (signal != 1) exit(1);
		}
	}
	fclose(csv);
	return (df) {nrow, ncol, colnames, var};
}
