#include "random.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <threads.h>
#include <time.h>

// https://prng.di.unimi.it/

thread_local u64 seedseed_ = 0;
thread_local u64 seed_[4] = {0};

u64 splitmix64() {
	seedseed_ += 0x9e3779b97f4a7c15;
	u64 z = seedseed_;
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void rinit(u64 seed) {
	seedseed_ = seed;
	if (seed == 0) {
		struct timespec time;
		timespec_get(&time, TIME_UTC);
		seedseed_ = time.tv_nsec;
	}
	seed_[0] = splitmix64();
	seed_[1] = splitmix64();
	seed_[2] = splitmix64();
	seed_[3] = splitmix64();
}

u64 rotl(u64 x, u64 k) {return (x << k) | (x >> (64 - k));}
u64 xoshiro256starstar(void) {
	u64 result = rotl(seed_[1] * 5, 7) * 9;
	u64 t = seed_[1] << 17;
	seed_[2] ^= seed_[0];
	seed_[3] ^= seed_[1];
	seed_[1] ^= seed_[2];
	seed_[0] ^= seed_[3];
	seed_[2] ^= t;
	seed_[3] = rotl(seed_[3], 45);
	return result;
}
f64 u01(void) {return (xoshiro256starstar() >> 11) * 0x1.0p-53;}

void rjump(void) {
	u64 jump[] = {
		0x180ec6d33cfd0aba,
		0xd5a61266f0c9392c,
		0xa9582618e03fc9aa,
		0x39abdc4529b1661c
	};
	u64 s0 = 0;
	u64 s1 = 0;
	u64 s2 = 0;
	u64 s3 = 0;
	for (u64 i = 0; i < 4; i++) {
		for (u64 b = 0; b < 64; b++) {
			if (jump[i] & 1ull << b) {
				s0 ^= seed_[0];
				s1 ^= seed_[1];
				s2 ^= seed_[2];
				s3 ^= seed_[3];
			}
			xoshiro256starstar();
		}
	}
	seed_[0] = s0;
	seed_[1] = s1;
	seed_[2] = s2;
	seed_[3] = s3;
}

// Sampling -------------------------------------------------------------------

vec sample_yes_rep(vec x, u64 size) {
	vec s = vec_new(size);
	for (u64 i = 0; i < size; i++) {
		u64 index = xoshiro256starstar() % x.len;
		s.x[i] = x.x[index];
	}
	return s;
}

vec sample_no_rep(vec x, u64 size) {
	vec tmp = vec_new(size);
	for (u64 i = 0, m = 0; i < x.len; i++) {
		f64 u = u01();
		if ((x.len - i) * u < size - m) tmp.x[m++] = x.x[i];
	}
	vec s = vec_new(size);
	for (u64 i = 0; i < size; i++) {
		u64 j = xoshiro256starstar() % (i + 1);
		s.x[i] = s.x[j];
		s.x[j] = tmp.x[i];
	}
	vec_free(tmp);
	return s;
}

vec sample(vec x, u64 size, u64 replacement) {
	if (seedseed_ == 0) rinit(0);
	if (replacement == 0) return sample_no_rep(x, size);
	return sample_yes_rep(x, size);
}

// Xorshift: Uniform ----------------------------------------------------------

vec runif(u64 n, f64 min, f64 max) {
	if (seedseed_ == 0) rinit(0);
	f64 *u = malloc(n * sizeof u[0]);
	for (u64 i = 0; i < n; i++) {
		u[i] = min + (max - min) * u01();
	}
	return (vec) {n, u};
}

// Discrete inversion: Bernoulli, Geometric, Poisson --------------------------

vec rber(u64 n, f64 prob) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = x.x[i] < prob;
	}
	return x;
}

vec rgeom(u64 n, f64 prob) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = floor(log(x.x[i]) / log1p(-prob));
	}
	return x;
}

vec rpois(u64 n, f64 lambda) {
	f64 *x = malloc(n * sizeof x[0]);
	vec u = runif(n, 0, 1);
	f64 e = exp(-lambda);
	for (u64 i = 0; i < n; i++) {
		f64 p = e;
		f64 F = p;
		u64 j = 0;
		for (j = 0; u.x[i] >= F; j++) {
			p *= lambda / (j + 1);
			F += p;
		}
		x[i] = j;
	}
	return (vec) {n, x};
}

// Relation to Bernoulli/Geometric: Binomial, Negative binomial ---------------

vec rbinom(u64 n, u64 size, f64 prob) {
	f64 *x = malloc(n * sizeof x[0]);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(size, 0, 1);
		x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			x[i] += u.x[j] < prob;
		}
		free(u.x);
	}
	return (vec) {n, x};
}

vec rnbinom(u64 n, u64 size, f64 prob) {
	f64 *x = malloc(n * sizeof x[0]);
	for (u64 i = 0; i < n; i++) {
		vec g = rgeom(size, prob);
		x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			x[i] += g.x[j];
		}
		free(g.x);
	}
	return (vec) {n, x};
}

// Continuous inversion: Exponential, Weibull, Cauchy, Logistic ---------------

vec rexp(u64 n, f64 rate) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = log(x.x[i]) / -rate;
	};
	return x;
}

vec rweibull(u64 n, f64 shape, f64 rate) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = pow(-log(x.x[i]), 1 / shape) / rate;
	}
	return x;
}

vec rcauchy(u64 n, f64 location, f64 scale) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = location + scale * tan(M_PI * x.x[i]);
	}
	return x;
}

vec rlogis(u64 n, f64 location, f64 scale) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = location + scale * log(x.x[i] / (1 - x.x[i]));
	}
	return x;
}

// Rejection: Gamma -----------------------------------------------------------

vec rgamma(u64 n, f64 shape, f64 rate) {
	rinit(0);
	f64 *x = malloc(n * sizeof x[0]);
	u64 correct = shape >= 1 ? 1 : 0;
	if (!correct) shape += 1;
	f64 d = shape - 1.0 / 3;
	f64 c = 1 / sqrt(9 * d);
	f64 u, z, v;
	for (u64 i = 0; i < n; i++) {
		do {
			do {
				z = sqrt(-2 * log(u01())) *
				cos(2 * M_PI * u01());
				v = 1 + c * z;
			} while (v <= 0);
			v *= v * v;
			z *= z;
			u = u01();
		} while (
			(u > 1 - 0.0331 * z * z) &&
			log(u) > 0.5 * z + d * (1 - v + log(v))
		);
		if (correct) x[i] = d * v / rate;
		else x[i] = d * v / rate * pow(u01(), 1 / (shape - 1));
	}
	return (vec) {n, x};
}

// Relation to Gamma: Chi-squared, F, Beta ------------------------------------

vec rchisq(u64 n, f64 df) {
	return rgamma(n, df / 2, 0.5);
}

vec rf(u64 n, f64 df1, f64 df2) {
	vec x = rchisq(n, df1);
	vec c = rchisq(n, df2);
	f64 ratio = df1 / df2;
	for (u64 i = 0; i < n; i++) {
		x.x[i] /= c.x[i] * ratio;
	}
	free(c.x);
	return x;
}

vec rbeta(u64 n, f64 shape1, f64 shape2) {
	vec x = rgamma(n, shape1, 1);
	vec g = rgamma(n, shape2, 1);
	for (u64 i = 0; i < n; i++) {
		x.x[i] /= x.x[i] + g.x[i];
	}
	free(g.x);
	return x;
}

// Box Muller: Normal ---------------------------------------------------------

vec rnorm(u64 n, f64 mean, f64 sd) {
	f64 *x = malloc(n * sizeof x[0]);
	vec u = runif(n + 1, 0, 1);
	for (u64 i = 0; i < n; i += 2) {
		f64 R = sd * sqrt(-2 * log(u.x[i]));
		f64 theta = 2 * M_PI * u.x[i + 1];
		x[i] = mean + R * sin(theta);
		if (i + 1 == n) break;
		x[i + 1] = mean + R * cos(theta);
	}
	return (vec) {n, x};
}

// Relation to Normal: Log normal, T ------------------------------------------

vec rlnorm(u64 n, f64 meanlog, f64 sdlog) {
	vec x = rnorm(n, meanlog, sdlog);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = exp(x.x[i]);
	}
	return x;
}

vec rt(u64 n, f64 df) {
	if (df == 1) return rcauchy(n, 0, 1);
	vec x = rnorm(n, 0, 1);
	vec c = rchisq(n, df);
	for (u64 i = 0; i < n; i++) {
		x.x[i] *= sqrt(df / c.x[i]);
	}
	free(c.x);
	return x;
}

/*
 * Limitations: ---------------------------------------------------------------
 * Poisson is O(n * lambda)
 * Binomial and Negative binomial are O(n * size)
 * No Hypergeometric
 */
