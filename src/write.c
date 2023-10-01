#include "../kek.h"

void write_vec(vec x, s64 path) {
	FILE *csv = fopen(path, "w");
	fputs("vec\n", csv);
	for (u64 i = 0; i < x.len; i++) {
		fprintf(csv, "%.17lf\n", x.x[i]);
	}
	fclose(csv);
}

void write_vec_dat(vec x, s64 path) {
	FILE *dat = fopen(path, "wb");
	fwrite(x.x, sizeof x.x[0], x.len, dat);
	fclose(dat);
}

void write_mat(mat x, s64 path) {
	FILE *csv = fopen(path, "w");
	for (u64 j = 0; j < x.len; j++) {
		fprintf(csv, "%s,", x.colnames[j]);
	}
	fputs("\n", csv);
	for (u64 i = 0; i < x.x[0].len; i++) {
		for (u64 j = 0; j < x.len; j++) {
			fprintf(csv, "%lg,", x.x[j].x[i]);
		}
		fputs("\n", csv);
	}
	fclose(csv);

}
