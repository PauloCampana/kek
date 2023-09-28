#include "../kek.h"

void write_vec(vec x, s64 path) {
	FILE *csv = fopen(path, "w");
	fputs(object_as_string(x) "\n", csv);
	for (u64 i = 0; i < x.len; i++) {
		fprintf(csv, "%.16lf\n", x.x[i]);
	}
	fclose(csv);
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
