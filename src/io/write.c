#include "io.h"
#include <stdio.h>

void write_vec(vec x, s64 path) {
	FILE *csv = fopen(path, "w");
	fputs("vec\n", csv);
	for (u64 i = 0; i < x.len; i++) {
		fprintf(csv, "%.17lf\n", x.x[i]);
	}
	fclose(csv);
}

void write_mat(mat x, s64 path) {
	FILE *csv = fopen(path, "w");
	for (u64 j = 0; j < x.len; j++) {
		fprintf(csv, "%s", x.colnames[j]);
		if (j != x.len - 1) fputc(',', csv);
	}
	fputs("\n", csv);
	for (u64 i = 0; i < x.x[0].len; i++) {
		for (u64 j = 0; j < x.len; j++) {
			fprintf(csv, "%lg", x.x[j].x[i]);
			if (j != x.len - 1) fputc(',', csv);
		}
		fputs("\n", csv);
	}
	fclose(csv);

}
