#include "../kek.h"
#include <stdio.h>
#include <stdlib.h>

mat read_mat(s64 path, u64 nrow, u64 ncol) {
	vec *x = malloc(ncol * sizeof *x);
	s64 *colnames = malloc(ncol * sizeof *colnames);
	s64 *rownames = malloc(nrow * sizeof *rownames);
	FILE *csv = fopen(path, "r");
	for (u64 j = 0; j < ncol; j++) {
		x[j].len = nrow;
		x[j].x = malloc(nrow * sizeof x[j].x);
		colnames[j] = malloc(64);
		u64 signal = fscanf(csv, "\n%[^,;\t\n],", colnames[j]);
		if (signal != 1) exit(1);
	}
	s64 buffer = malloc(64);
	for (u64 i = 0; i < nrow; i++) {
		rownames[i] = malloc(64);
		sprintf(rownames[i], "%llu", i + 1);
		for (u64 j = 0; j < ncol; j++) {
			u64 signal = fscanf(csv, "\n%[^,;\t\n],", buffer);
			if (signal != 1) exit(1);
			x[j].x[i] = strtod(buffer, NULL);
		}
	}
	fclose(csv);
	return (mat) {ncol, colnames, rownames, x};
}
