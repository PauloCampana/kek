#include "../kek.h"
#include <math.h>

vec vec_apply1(vec x, f64 fun(f64)) {
	vec r = vec_new(x.len);
	for (u64 i = 0; i < r.len; i++) {
		r.x[i] = fun(x.x[i]);
	}
	return r;
}

vec vec_apply2(vec x, vec y, f64 fun(f64, f64)) {
	vec r = vec_new(x.len);
	for (u64 i = 0; i < r.len; i++) {
		r.x[i] = fun(x.x[i], y.x[i]);
	}
	return r;
}

vec vec_apply3(vec x, vec y, vec z, f64 fun(f64, f64, f64)) {
	vec r = vec_new(x.len);
	for (u64 i = 0; i < r.len; i++) {
		r.x[i] = fun(x.x[i], y.x[i], z.x[i]);
	}
	return r;
}

vec vec_standardize(vec x) {
	vec y = vec_new(x.len);
	f64 mean = vec_mean(x);
	f64 sd = vec_sd(x);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = (x.x[i] - mean) / sd;
	}
	return y;
}

vec vec_add(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < z.len; i++) {
		z.x[i] = x.x[i] + y.x[i];
	}
	return z;
}

vec vec_subtract(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < z.len; i++) {
		z.x[i] = x.x[i] - y.x[i];
	}
	return z;
}

vec vec_multiply(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < z.len; i++) {
		z.x[i] = x.x[i] * y.x[i];
	}
	return z;
}

vec vec_divide(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < z.len; i++) {
		z.x[i] = x.x[i] / y.x[i];
	}
	return z;
}

vec vec_round(vec x) {
	vec y = vec_new(x.len);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = rint(x.x[i]);
	}
	return y;
}

vec vec_floor(vec x) {
	vec y = vec_new(x.len);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = floor(x.x[i]);
	}
	return y;
}

vec vec_ceiling(vec x) {
	vec y = vec_new(x.len);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = ceil(x.x[i]);
	}
	return y;
}

vec vec_truncate(vec x) {
	vec y = vec_new(x.len);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = trunc(x.x[i]);
	}
	return y;
}
