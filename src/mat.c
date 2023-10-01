#include "../kek.h"

vec mat_vec(mat x, s64 name) {
	vec z;
	for (u64 i = 0; i < x.len; i++) {
		u64 cmp = strcmp(x.colnames[i], name);
		if (cmp == 0) z = x.x[i];
	}
	return z;
}

mat mat_transpose(mat x) {
	vec *t = malloc(x.x[0].len * sizeof *t);
	for (u64 j = 0; j < x.x[0].len; j++) {
		t[j].len = x.len;
		t[j].x = malloc(x.len * sizeof t[j].x);
		for (u64 i = 0; i < x.len; i++) {
			t[j].x[i] = x.x[i].x[j];
		}
	}
	return (mat) {x.x[0].len, x.rownames, x.colnames, t};
}

mat mat_multiply(mat x, mat y) {
	vec *z = malloc(y.len * sizeof *z);
	s64 *colnames = malloc(y.len * sizeof *colnames);
	s64 *rownames = malloc(x.x[0].len * sizeof *rownames);
	for (u64 j = 0; j < y.len; j++) {
		z[j].len = x.x[0].len;
		z[j].x = malloc(x.x[0].len * sizeof z[j].x);
		colnames[j] = y.colnames[j];
		for (u64 i = 0; i < x.x[0].len; i++) {
			if (j == 0) rownames[i] = x.rownames[i];
			z[j].x[i] = 0;
			for (u64 l = 0; l < x.len; l++) {
				z[j].x[i] += x.x[l].x[i] * y.x[j].x[l];
			}
		}
	}
	return (mat) {y.len, colnames, rownames, z};
}
