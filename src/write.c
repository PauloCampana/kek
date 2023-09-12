#include "../kek.h"

void write_vec(vec x, char *path) {
	FILE *csv = fopen(path, "w");
	fprintf(csv, "col\n");
	for (u64 i = 0; i < x.len; i++) {
		switch (x.type) {
        case INTEGER:
            fprintf(csv, "%lli\n", i64(x)[i]);
            break;
        case UNSIGNED:
            fprintf(csv, "%llu\n", u64(x)[i]);
            break;
        case FLOAT:
            fprintf(csv, "%.16lf\n", f64(x)[i]);
            break;
        }
	}
	fclose(csv);
}
