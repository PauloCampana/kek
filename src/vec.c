#include "../kek.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

vec vec_new(u64 n) {
	f64 *x = malloc(n * sizeof x[0]);
	return (vec) {n, x};
}

vec vec_copy(vec x) {
	vec y = vec_new(x.len);
	memcpy(y.x, x.x, x.len * sizeof x.x[0]);
	return y;
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

vec vec_rep(vec x, u64 times, u64 each) {
	vec y = vec_new(x.len * times * each);
	for (u64 t = 0; t < times; t++) {
		for (u64 i = 0; i < x.len; i++) {
			for (u64 e = 0; e < each; e++) {
				y.x[each * (x.len * t + i) + e] = x.x[i];
			}
		}
	}
	return y;
}

vec vec_unique(vec x) {
	vec y = vec_new(x.len);
	u64 k = 0;
	for (u64 i = 0; i < x.len; i++) {
		y.x[k] = x.x[i];
		u64 unique = 1;
		for (u64 j = 0; j < i; j++) {
			if (y.x[k] == x.x[j]) unique = 0;
		}
		if (unique == 1) k++;
	}
	y.len = k;
	y.x = realloc(y.x, y.len * sizeof y.x[0]);
	return y;
}

vec vec_combine(vec x, vec y) {
	vec z = vec_new(x.len + y.len);
	memcpy(z.x, x.x, x.len * sizeof x.x[0]);
	memcpy(z.x + x.len, y.x, y.len * sizeof y.x[0]);
	return z;
}

int kek_sortfun(const void *x, const void *y) {
	f64 diff = *(f64 *) x - *(f64 *) y;
	return diff > 0 ? 1 : -1;
}
vec vec_sort(vec x) {
	vec y = vec_copy(x);
	qsort(y.x, y.len, sizeof y.x[0], kek_sortfun);
	return y;
}

vec vec_reverse(vec x) {
	vec y = vec_new(x.len);
	for (u64 i = 0; i < y.len; i++) {
		y.x[i] = x.x[y.len - i - 1];
	}
	return y;
}

vec vec_accumulate(vec x) {
	vec z = vec_new(x.len);
	z.x[0] = x.x[0];
	for (u64 i = 1; i < z.len; i++) {
		z.x[i] = x.x[i] + z.x[i - 1];
	}
	return z;
}

u64 vec_all(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		if (x.x[i] == 0) return 0;
	}
	return 1;
}

u64 vec_any(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		if (x.x[i] != 0) return 1;
	}
	return 0;
}

f64 vec_min(vec x) {
	f64 min = x.x[0];
	for (u64 i = 1; i < x.len; i++) {
		if (x.x[i] < min) min = x.x[i];
	}
	return min;
}

f64 vec_max(vec x) {
	f64 max = x.x[0];
	for (u64 i = 1; i < x.len; i++) {
		if (x.x[i] > max) max = x.x[i];
	}
	return max;
}

vec vec_in(vec x, vec y) {
	vec z = vec_new(x.len);
	for (u64 i = 0; i < z.len; i++) {
		u64 in = 0;
		for (u64 j = 0; j < y.len; j++) {
			if (x.x[i] == y.x[j]) {
				in = 1;
				break;
			}
		}
		z.x[i] = in;
	}
	return z;
}

vec vec_which(vec x, s64 op, f64 value) {
	vec y = vec_new(x.len);
	u64 j = 0;
	for (u64 i = 0; i < y.len; i++) {
		switch (op[0] + op[1]) {
		case '=' + '=':
			if (x.x[i] == value) y.x[j++] = i;
			break;
		case '!' + '=':
			if (x.x[i] != value) y.x[j++] = i;
			break;
		case '>' + '=':
			if (x.x[i] >= value) y.x[j++] = i;
			break;
		case '<' + '=':
			if (x.x[i] <= value) y.x[j++] = i;
			break;
		case '>':
			if (x.x[i] >  value) y.x[j++] = i;
			break;
		case '<':
			if (x.x[i] <  value) y.x[j++] = i;
			break;
		}
	}
	y.len = j;
	y.x = realloc(y.x, y.len * sizeof y.x[0]);
	return y;
}

vec vec_filter(vec x, s64 op, f64 value) {
	vec index = vec_which(x, op, value);
	vec y = vec_new(index.len);
	for (u64 i = 0; i < index.len; i++) {
		y.x[i] = x.x[llrint(index.x[i])];
	}
	vec_free(index);
	return y;
}
