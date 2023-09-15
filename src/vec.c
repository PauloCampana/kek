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

vec vec_add(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < x.len; i++) {
		z.x[i] = x.x[i] + y.x[i];
	}
	return z;
}
