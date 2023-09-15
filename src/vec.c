#include "../kek.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vec vec_new(u64 type, u64 n) {
	u64 size = 0;
	switch (type) {
	case SIGNED:
		size = sizeof(i64);
		break;
	case UNSIGNED:
		size = sizeof(u64);
		break;
	case FLOAT:
		size = sizeof(f64);
		break;
	case CHAR:
		size = sizeof(c64);
		break;
	case STRING:
		size = sizeof(s64);
		break;
	}
	void *x = malloc(n * size);
	return (vec) {type, n, x};
}

void vec_free(vec x) {
	free(x.x);
}

vec vec_fill(vec x, f64 value) {
	for (u64 i = 0; i < x.len; i++) {
		switch (x.type) {
		case SIGNED:
			i64(x)[i] = value;
		 	break;
		case UNSIGNED:
			u64(x)[i] = value;
			break;
		case FLOAT:
			f64(x)[i] = value;
			break;
		case CHAR:
			c64(x)[i] = value;
			break;
		}
	}
	return x;
}

vec vec_seq(vec x, f64 start, f64 by) {
	for (u64 i = 0; i < x.len; i++) {
		switch (x.type) {
		case SIGNED:
			i64(x)[i] = start + by * i;
		 	break;
		case UNSIGNED:
			u64(x)[i] = start + by * i;
			break;
		case FLOAT:
			f64(x)[i] = start + by * i;
			break;
		}
	}
	return x;
}

vec vec_combine(vec x, vec y) {
	vec z = vec_new(FLOAT, x.len + y.len);

	return z;
}

vec vec_add(vec x, vec y) {
	vec z = vec_new(FLOAT, x.len);
	for (u64 i = 0; i < x.len; i++) {
		switch (x.type) {
		case SIGNED:
			f64(z)[i] = i64(x)[i];
		 	break;
		case UNSIGNED:
			f64(z)[i] = u64(x)[i];
			break;
		case FLOAT:
			f64(z)[i] = f64(x)[i];
			break;
		}
		switch (y.type) {
		case SIGNED:
			f64(z)[i] += i64(y)[i];
		 	break;
		case UNSIGNED:
			f64(z)[i] += u64(y)[i];
			break;
		case FLOAT:
			f64(z)[i] += f64(y)[i];
			break;
		}
	}
	return z;
}
