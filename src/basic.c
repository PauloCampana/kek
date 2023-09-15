#include "../kek.h"
#include <stdlib.h>

u64 all(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		if (x.x[i] == 0) return 0;
	}
	return 1;
}

u64 any(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		if (x.x[i] != 0) return 1;
	}
	return 0;
}

vec which(vec x, s64 op, f64 value) {
	f64 *w = malloc(x.len * sizeof *w);
	u64 j = 0;
	for (u64 i = 0; i < x.len; i++) {
		switch (*op) {
		case '=':
			if (x.x[i] == value) w[j++] = i;
			break;
		case '!':
			if (x.x[i] != value) w[j++] = i;
			break;
		case '>':
			if (x.x[i] > value) w[j++] = i;
			break;
		case '<':
			if (x.x[i] < value) w[j++] = i;
			break;
		}
	}
	w = realloc(w, j * sizeof *w);
	return (vec) {j, w};
}
