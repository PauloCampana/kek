#include "../kek.h"
#include <stdio.h>
#include <stdlib.h>

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
	mat x = mat_new(nrow, ncol);
	for (u64 j = 0; j < ncol; j++) {
		x.x[j] = vec_new(nrow);
		u64 signal = fscanf(csv, "\n%[^,;\t\n],", x.colnames[j]);
		if (signal != 1) exit(1);
	}
	c64 buffer[64];
	for (u64 i = 0; i < nrow; i++) {
		sprintf(x.rownames[i], "%llu", i);
		for (u64 j = 0; j < ncol; j++) {
			u64 signal = fscanf(csv, "\n%[^,;\t\n],", buffer);
			if (signal != 1) exit(1);
			x.x[j].x[i] = strtod(buffer, NULL);
		}
	}
	fclose(csv);
	return x;
}
