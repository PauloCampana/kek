#include "../kek.h"

// https://prng.di.unimi.it/

thread_local u64 _seedseed = 0;
thread_local u64 _seed[4] = {0};

u64 splitmix64() {
	u64 z = (_seedseed += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void rinit(u64 seed) {
	_seedseed = seed;
	if (seed == 0) {
		struct timespec time;
		timespec_get(&time, TIME_UTC);
		_seedseed = time.tv_nsec;
	}
	_seed[0] = splitmix64();
	_seed[1] = splitmix64();
	_seed[2] = splitmix64();
	_seed[3] = splitmix64();
}

u64 rotl(u64 x, u64 k) {return (x << k) | (x >> (64 - k));}
u64 xoshiro256starstar(void) {
	u64 result = rotl(_seed[1] * 5, 7) * 9;
	u64 t = _seed[1] << 17;
	_seed[2] ^= _seed[0];
	_seed[3] ^= _seed[1];
	_seed[1] ^= _seed[2];
	_seed[0] ^= _seed[3];
	_seed[2] ^= t;
	_seed[3] = rotl(_seed[3], 45);
	return result;
}

void rjump(void) {
	u64 JUMP[] = {
		0x180ec6d33cfd0aba,
		0xd5a61266f0c9392c,
		0xa9582618e03fc9aa,
		0x39abdc4529b1661c
	};
	u64 s0 = 0, s1 = 0, s2 = 0, s3 = 0;
	for (u64 i = 0; i < sizeof JUMP / sizeof *JUMP; i++) {
		for (u64 b = 0; b < 64; b++) {
			if (JUMP[i] & 1ull << b) {
				s0 ^= _seed[0];
				s1 ^= _seed[1];
				s2 ^= _seed[2];
				s3 ^= _seed[3];
			}
			xoshiro256starstar();
		}
	}
	_seed[0] = s0;
	_seed[1] = s1;
	_seed[2] = s2;
	_seed[3] = s3;
}

// Xorshift: Uniform ---------------------------------------------------------

vec runif(u64 n, f64 min, f64 max) {
	if (_seedseed == 0) rinit(0);
	f64 *u = malloc(n * sizeof *u);
	for (u64 i = 0; i < n; i++) {
		f64 u01 = (xoshiro256starstar() >> 11) * 0x1.0p-53;
		u[i] = min + (max - min) * u01;
	}
	return (vec) {n, u};
}

// Discrete inversion: Bernoulli, Geometric, Poisson -------------------------

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
	f64 *x = malloc(n * sizeof *x);
	vec u = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64 p = exp(-lambda);
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

// Relation to Bernoulli/Geometric: Binomial, Negative binomial --------------

vec rbinom(u64 n, u64 size, f64 prob) {
	f64 *x = malloc(n * sizeof *x);
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
	f64 *x = malloc(n * sizeof *x);
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

// Continuous inversion: Exponential, Weibull, Cauchy, Logistic --------------

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

// Relation to Exponential: Gamma, Chi-squared, F, beta ----------------------

vec rgamma(u64 n, u64 shape, f64 rate) {
	f64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(shape, 0, 1);
		x[i] = 0;
		for (u64 j = 0; j < shape; j++) {
			x[i] -= log(u.x[j]);
		}
		x[i] /= rate;
		free(u.x);
	}
	return (vec) {n, x};
}

vec rchisq(u64 n, u64 df) {
	f64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(df / 2, 0, 1);
		x[i] = 0;
		for (u64 j = 0; j < df / 2; j++) {
			x[i] -= log(u.x[j]);
		}
		x[i] *= 2;
		free(u.x);
	}
	if (df % 2 == 1) {
		vec z = rnorm(n, 0, 1);
		for (u64 i = 0; i < n; i++) {
			x[i] += z.x[i] * z.x[i];
		}
		free(z.x);
	}
	return (vec) {n, x};
}

vec rf(u64 n, u64 df1, u64 df2) {
	vec x = rchisq(n, df1);
	vec c = rchisq(n, df2);
	for (u64 i = 0; i < n; i++) {
		x.x[i] /= c.x[i] * df1 / df2;
	}
	return x;
}

vec rbeta(u64 n, u64 shape1, u64 shape2) {
	f64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(shape1 + shape2, 0, 1);
		f64 num = 0;
		for (u64 j = 0; j < shape1; j++) {
			num -= log(u.x[j]);
		}
		f64 den = num;
		for (u64 j = shape1; j < shape1 + shape2; j++) {
			den -= log(u.x[j]);
		}
		x[i] = num / den;
		free(u.x);
	}
	return (vec) {n, x};
}

// Box Muller: Normal --------------------------------------------------------

vec rnorm(u64 n, f64 mean, f64 sd) {
	f64 *x = malloc(n * sizeof *x);
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

// Relation to Normal: Log normal, T -----------------------------------------

vec rlnorm(u64 n, f64 meanlog, f64 sdlog) {
	vec x = rnorm(n, meanlog, sdlog);
	for (u64 i = 0; i < n; i++) {
		x.x[i] = exp(x.x[i]);
	}
	return x;
}

vec rt(u64 n, u64 df) {
	if (df == 1) return rcauchy(n, 0, 1);
	vec x = rnorm(n, 0, 1);
	vec c = rchisq(n, df);
	for (u64 i = 0; i < n; i++) {
		x.x[i] *= sqrt(df / c.x[i]);
	}
	return x;
}

/*
 * Limitations: --------------------------------------------------------------
 * Poisson is O(n * lambda)
 * Binomial and Negative binomial are O(n * size)
 * No Hypergeometric
 * Gamma, Beta, Chi-squared, F and t need integer shape and df parameters
 * 	Gamma       O(n * shape)
 * 	Beta        O(n * (shape1 + shape2))
 * 	Chi-squared O(n * df)
 * 	F           O(n * (df1 + df2))
 * 	t           O(n * df)
 */
