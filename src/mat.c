#include "../kek.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

mat mat_new(u64 nrow, u64 ncol) {
	vec *x = malloc(ncol * sizeof x[0]);
	c64 (*colnames)[64] = malloc(ncol * sizeof colnames[0]);
	c64 (*rownames)[64] = malloc(nrow * sizeof rownames[0]);
	for (u64 j = 0; j < ncol; j++) {
		x[j] = vec_new(nrow);
		memset(colnames[j], 0, 64);
	}
	for (u64 i = 0; i < nrow; i++) {
		memset(rownames[i], 0, 64);
	}
	return (mat) {ncol, colnames, rownames, x};
}

mat mat_copy(mat x) {
	u64 ncol = x.len;
	u64 nrow = x.x->len;
	mat y = mat_new(nrow, ncol);
	for (u64 j = 0; j < ncol; j++) {
		y.x[j] = vec_copy(x.x[j]);
		strncpy(y.colnames[j], x.colnames[j], sizeof y.colnames[0]);
	}
	for (u64 i = 0; i < nrow; i++) {
		strncpy(y.rownames[i], x.rownames[i], sizeof y.rownames[0]);
	}
	return y;
}

void mat_free(mat x) {
	for (u64 j = 0; j < x.len; j++) {
		vec_free(x.x[j]);
	}
	free(x.colnames);
	free(x.rownames);
	free(x.x);
}

vec mat_vec(mat x, s64 name) {
	vec z;
	for (u64 j = 0; j < x.len; j++) {
		u64 cmp = strcmp(x.colnames[j], name);
		if (cmp == 0) z = vec_copy(x.x[j]);
	}
	return z;
}

mat mat_transpose(mat x) {
	u64 nrow = x.len;
	u64 ncol = x.x->len;
	mat y = mat_new(nrow, ncol);
	for (u64 i = 0; i < nrow; i++) {
		strncpy(y.rownames[i], x.colnames[i], sizeof y.rownames[0]);
	}
	for (u64 j = 0; j < ncol; j++) {
		strncpy(y.colnames[j], x.rownames[j], sizeof y.colnames[0]);
		for (u64 i = 0; i < nrow; i++) {
			y.x[j].x[i] = x.x[i].x[j];
		}
	}
	return y;
}

mat mat_multiply(mat x, mat y) {
	if (x.len != y.x->len) exit(1);
	u64 nrow = x.x->len;
	u64 ncol = y.len;
	u64 nother = x.len;
	mat z = mat_new(nrow, ncol);
	for (u64 i = 0; i < nrow; i++) {
		strncpy(z.rownames[i], x.rownames[i], sizeof z.rownames[0]);
	}
	for (u64 j = 0; j < ncol; j++) {
		strncpy(z.colnames[j], y.colnames[j], sizeof z.colnames[0]);
		for (u64 i = 0; i < nrow; i++) {
			z.x[j].x[i] = 0;
			for (u64 k = 0; k < nother; k++) {
				z.x[j].x[i] += x.x[k].x[i] * y.x[j].x[k];
			}
		}
	}
	return z;
}

mat mat_submat(mat x, vec rows, vec cols) {
	mat y = mat_new(rows.len, cols.len);
	for (u64 i = 0; i < rows.len; i++) {
		u64 row = llrint(rows.x[i]);
		strncpy(y.rownames[i], x.rownames[row], sizeof y.rownames[0]);
	}
	for (u64 j = 0; j < cols.len; j++) {
		u64 col = llrint(cols.x[j]);
		strncpy(y.colnames[j], x.colnames[col], sizeof y.colnames[0]);
		for (u64 i = 0; i < rows.len; i++) {
			u64 row = llrint(rows.x[i]);
			y.x[j].x[i] = x.x[col].x[row];
		}
	}
	return y;
}

f64 mat_determinant(mat x) {
	if (x.len != x.x->len) return NAN;
	mat y = mat_copy(x);
	u64 n = y.len;
	for (u64 k = 0; k < n - 1; k++) {
		for (u64 j = k + 1; j < n; j++) {
			for (u64 i = k + 1; i < n; i++) {
				f64 num1 = y.x[j].x[i] * y.x[k].x[k];
				f64 num2 = y.x[k].x[i] * y.x[j].x[k];
				f64 den = k == 0 ? 1 : y.x[k - 1].x[k - 1];
				y.x[j].x[i] = (num1 - num2) / den;
			}
		}
	}
	f64 result = y.x[n - 1].x[n - 1];
	mat_free(y);
	return result;
}

mat mat_inverse(mat x) {
	f64 det = mat_determinant(x);
	mat y = mat_copy(x);
	u64 n = y.len;
	for (u64 j = 0; j < n; j++) {
		for (u64 i = 0; i < n; i++) {
			vec rows = vec_new(n - 1);
			for (u64 k = 0, tmp = 0; k < rows.len; k++, tmp++) {
				if (tmp == i) tmp++;
				rows.x[k] = tmp;
			}
			vec cols = vec_new(n - 1);
			for (u64 k = 0, tmp = 0; k < cols.len; k++, tmp++) {
				if (tmp == j) tmp++;
				cols.x[k] = tmp;
			}
			mat minor = mat_submat(x, rows, cols);
			f64 cofactor = mat_determinant(minor);
			vec_free(rows);
			vec_free(cols);
			mat_free(minor);
			y.x[i].x[j] = pow(-1, i + j) * cofactor / det;
		}
	}
	return y;
}
