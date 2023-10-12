#include "random.h"
#include <math.h>

f64 random_gamma_single(f64 d, f64 c) {
	f64 u, z, v;
	do {
		do {
			z = random_normal_single();
			v = 1 + c * z;
		} while (v <= 0);
		v *= v * v;
		z *= z;
		u = random_f64();
	} while (
		(u > 1 - 0.0331 * z * z) &&
		log(u) > 0.5 * z + d * (1 - v + log(v))
	);
	return d * v;
}

vec random_gamma(u64 n, f64 shape, f64 rate) {
	random_seed(0);
	vec gamma = vec_new(n);
	u64 correct = 1;
	if (shape < 1) {
		correct = 0;
		shape++;
	}
	f64 d = shape - 1.0 / 3;
	f64 c = 1 / sqrt(9 * d);
	if (correct) {
		for (u64 i = 0; i < n; i++) {
			f64 g = random_gamma_single(d, c);
			gamma.x[i] = g / rate;
		}
	} else {
		for (u64 i = 0; i < n; i++) {
			f64 g = random_gamma_single(d, c);
			f64 correction = pow(random_f64(), 1 / (shape - 1));
			gamma.x[i] = g * correction / rate;
		}
	}
	return gamma;
}
