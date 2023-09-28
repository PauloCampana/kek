#include "../kek.h"

vec vec_new(u64 n) {
	f64 *x = malloc(n * sizeof *x);
	return (vec) {n, x};
}

void vec_free(vec x) {
	free(x.x);
}

vec vec_fill(u64 n, f64 value) {
	vec x = vec_new(n);
	for (u64 i = 0; i < x.len; i++) {
		x.x[i] = value;
	}
	return x;
}

vec vec_seq(u64 n, f64 start, f64 by) {
	vec x = vec_new(n);
	for (u64 i = 0; i < x.len; i++) {
		x.x[i] = start + by * i;
	}
	return x;
}

vec vec_combine(vec x, vec y) {
	vec z = vec_new(x.len + y.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i];
	}
	for (u64 i = 0; i < y.len; i++) {
		z.x[x.len + i] = y.x[i];
	}
	return z;
}

int kek_sortfun(const void *x, const void *y) {
	f64 diff = *(f64 *) x - *(f64 *) y;
	return diff > 0 ? 1 : -1;
}
void vec_sort(vec x) {
	qsort(x.x, x.len, sizeof x.x[0], kek_sortfun);
}

vec vec_accumulate(vec x) {
	vec z = vec_new(x.len);
	z.x[0] = x.x[0];
	for (u64 i = 1; i < x.len; i++) {
		z.x[i] = x.x[i] + z.x[i - 1];
	}
	return z;
}

vec vec_add(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i] + y.x[i];
	}
	return z;
}

vec vec_subtract(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i] - y.x[i];
	}
	return z;
}

vec vec_multiply(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i] * y.x[i];
	}
	return z;
}

vec vec_divide(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i] / y.x[i];
	}
	return z;
}
