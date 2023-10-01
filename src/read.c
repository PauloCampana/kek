#include "../kek.h"

mat read_mat(s64 path) {
	FILE *csv = fopen(path, "r");
	u64 nrow, ncol;
	for (nrow = 0; fscanf(csv, "%*c") != EOF; nrow++) {
		fscanf(csv, "%*[^\n]");
	}
	nrow -= 2;
	rewind(csv);
	for (ncol = 1;;) {
		u64 c = fgetc(csv);
		if (c == ',') ncol++;
		if (c == '\n') break;
	}
	rewind(csv);
	vec *x = malloc(ncol * sizeof *x);
	s64 *colnames = malloc(ncol * sizeof *colnames);
	s64 *rownames = malloc(nrow * sizeof *rownames);
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
		sprintf(rownames[i], "%llu", i);
		for (u64 j = 0; j < ncol; j++) {
			u64 signal = fscanf(csv, "\n%[^,;\t\n],", buffer);
			if (signal != 1) exit(1);
			x[j].x[i] = strtod(buffer, NULL);
		}
	}
	fclose(csv);
	return (mat) {ncol, colnames, rownames, x};
}
