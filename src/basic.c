#include "../kek.h"
#include <stdlib.h>

u64 all(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		u64 b;
		switch (x.type) {
		case SIGNED:
			b = i64(x)[i] == 0;
		 	break;
		case UNSIGNED:
			b = u64(x)[i] == 0;
			break;
		case FLOAT:
			b = f64(x)[i] == 0;
			break;
		}
		if (b) return 0;
		if (i == x.len) b = 1;
	}
	return 1;
}

u64 any(vec x) {
	for (u64 i = 0; i < x.len; i++) {
		u64 b;
		switch (x.type) {
		case SIGNED:
			b = i64(x)[i] != 0;
		 	break;
		case UNSIGNED:
			b = u64(x)[i] != 0;
			break;
		case FLOAT:
			b = f64(x)[i] != 0;
			break;
		}
		if (b) return 1;
		if (i == x.len) b = 1;
	}
	return 0;
}

vec which(vec x, s64 op, f64 value) {
	u64 *w = malloc(x.len * sizeof *w);
	u64 j = 0;
	for (u64 i = 0; i < x.len; i++) {
		switch (*op) {
		case '=':
			switch (x.type) {
			case SIGNED:
				if (i64(x)[i] == value) w[j++] = i;
				break;
			case UNSIGNED:
				if (u64(x)[i] == value) w[j++] = i;
				break;
			case FLOAT:
				if (f64(x)[i] == value) w[j++] = i;
				break;
			}
			break;
		case '!':
			switch (x.type) {
			case SIGNED:
				if (i64(x)[i] != value) w[j++] = i;
				break;
			case UNSIGNED:
				if (u64(x)[i] != value) w[j++] = i;
				break;
			case FLOAT:
				if (f64(x)[i] != value) w[j++] = i;
				break;
			}
			break;
		case '>':
			switch (x.type) {
			case SIGNED:
				if (i64(x)[i] > value) w[j++] = i;
				break;
			case UNSIGNED:
				if (u64(x)[i] > value) w[j++] = i;
				break;
			case FLOAT:
				if (f64(x)[i] > value) w[j++] = i;
				break;
			}
			break;
		case '<':
			switch (x.type) {
			case SIGNED:
				if (i64(x)[i] < value) w[j++] = i;
				break;
			case UNSIGNED:
				if (u64(x)[i] < value) w[j++] = i;
				break;
			case FLOAT:
				if (f64(x)[i] < value) w[j++] = i;
				break;
			}
			break;
		}
	}
	w = realloc(w, j * sizeof *w);
	return (vec) {UNSIGNED, j, w};
}
