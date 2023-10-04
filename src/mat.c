#include "../kek.h"
#include <string.h>

mat mat_new(u64 nrow, u64 ncol) {
	vec *x = malloc(ncol * sizeof *x);
	s64 *colnames = malloc(ncol * sizeof *colnames);
	s64 *rownames = malloc(nrow * sizeof *rownames);
	for (u64 j = 0; j < ncol; j++) {
		x[j].len = nrow;
		x[j].x = malloc(nrow * sizeof x[j].x);
		colnames[j] = malloc(64);
		memset(colnames[j], 0, 64);
	}
	for (u64 i = 0; i < nrow; i++) {
		rownames[i] = malloc(64);
		memset(rownames[i], 0, 64);
	}
	return (mat) {ncol, colnames, rownames, x};
}

void mat_free(mat x) {
	for (u64 j = 0; j < x.len; j++) {
		free(x.x[j].x);
	}
	free(x.colnames);
	free(x.rownames);
	free(x.x);
}

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

mat mat_submat(mat x, vec rows, vec cols) {
	vec *y = malloc(cols.len * sizeof *y);
	s64 *colnames = malloc(cols.len * sizeof *colnames);
	s64 *rownames = malloc(rows.len * sizeof *rownames);
	for (u64 j = 0; j < cols.len; j++) {
		u64 col = llrint(cols.x[j]);
		y[j].len = rows.len;
		y[j].x = malloc(rows.len * sizeof y[j].x);
		colnames[j] = x.colnames[col];
		for (u64 i = 0; i < rows.len; i++) {
			u64 row = llrint(rows.x[i]);
			if (j == 0) rownames[i] = x.rownames[row];
			y[j].x[i] = x.x[col].x[row];
		}
	}

	return (mat) {cols.len, colnames, rownames, y};
}

f64 mat_determinant(mat x) {
	if (x.len != x.x[0].len) return NAN;
	if (x.len == 1) return x.x[0].x[0];
	f64 det = 0;
	for (u64 j = 0; j < x.len; j++) {
		vec rows = vec_seq(x.len - 1, 1, 1);
		vec cols = vec_new(x.len - 1);
		for (u64 k = 0, tmp = 0; k < x.len - 1; k++, tmp++) {
			if (k == j) tmp++;
			cols.x[k] = tmp;
		}
		mat adj = mat_submat(x, rows, cols);
		f64 detadj = mat_determinant(adj);
		det += pow(-1, j) * x.x[j].x[0] * detadj;
		mat_free(adj);
		vec_free(rows);
		vec_free(cols);
	}
	return det;
}
