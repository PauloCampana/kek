#include "random.h"

vec random_sample_with_replacement(vec x, u64 size) {
	vec s = vec_new(size);
	for (u64 i = 0; i < size; i++) {
		u64 index = random_u64() % x.len;
		s.x[i] = x.x[index];
	}
	return s;
}

vec random_sample_without_replacement(vec x, u64 size) {
	vec tmp = vec_new(size);
	for (u64 i = 0, m = 0; i < x.len; i++) {
		f64 u = random_f64();
		if ((x.len - i) * u < size - m) {
			tmp.x[m] = x.x[i];
			m++;
		}
	}
	vec s = vec_new(size);
	for (u64 i = 0; i < size; i++) {
		u64 j = random_u64() % (i + 1);
		s.x[i] = s.x[j];
		s.x[j] = tmp.x[i];
	}
	vec_free(tmp);
	return s;
}

vec random_sample(vec x, u64 size, u64 replacement) {
	random_seed(0);
	if (replacement == 0) {
		return random_sample_without_replacement(x, size);
	} else {
		return random_sample_with_replacement(x, size);
	}
}
