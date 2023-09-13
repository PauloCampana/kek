#include "../kek.h"

static u64 _seedseed = 0;
static u64 _seed[4] = {0};

u64 splitmix64() {
	u64 z = (_seedseed += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void rinit(u64 seed) {
	if (seed == 0) {
		struct timespec time;
		timespec_get(&time, TIME_UTC);
		_seedseed = time.tv_nsec;
	}
	else _seedseed = seed;
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

// Xorshift: Uniform ---------------------------------------------------------

vec runif(u64 n, f64 min, f64 max) {
	if (_seed[0] == 0) rinit(0);
	f64 *u = malloc(n * sizeof *u);
	for (u64 i = 0; i < n; i++) {
		f64 u01 = (xoshiro256starstar() >> 11) * 0x1.0p-53;
		u[i] = min + (max - min) * u01;
	}
	return (vec) {FLOAT, n, u};
}

// Discrete inversion: Bernoulli, Geometric, Poisson -------------------------

vec rber(u64 n, f64 prob) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		u64(x)[i] = f64(x)[i] < prob;
	}
	x.type = UNSIGNED;
	return x;
}

vec rgeom(u64 n, f64 prob) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		u64(x)[i] = log(f64(x)[i]) / log1p(-prob);
	}
	x.type = UNSIGNED;
	return x;
}

vec rpois(u64 n, f64 lambda) {
	u64 *x = malloc(n * sizeof *x);
	vec u = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64 p = exp(-lambda);
		f64 F = p;
		u64 j = 0;
		for (j = 0; f64(u)[i] >= F; j++) {
			p *= lambda / (j + 1);
			F += p;
		}
		x[i] = j;
	}
	return (vec) {UNSIGNED, n, x};
}

// Relation to Bernoulli/Geometric: Binomial, Negative binomial --------------

vec rbinom(u64 n, u64 size, f64 prob) {
	u64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(size, 0, 1);
		x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			x[i] += f64(u)[j] < prob;
		}
		free(f64(u));
	}
	return (vec) {UNSIGNED, n, x};
}

vec rnbinom(u64 n, u64 size, f64 prob) {
	u64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec g = rgeom(size, prob);
		x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			x[i] += u64(g)[j];
		}
		free(u64(g));
	}
	return (vec) {UNSIGNED, n, x};
}

// Continuous inversion: Exponential, Weibull, Cauchy, Logistic --------------

vec rexp(u64 n, f64 rate) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] = log(f64(x)[i]) / -rate;
	};
	return x;
}

vec rweibull(u64 n, f64 shape, f64 rate) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] = pow(-log(f64(x)[i]), 1 / shape) / rate;
		// f64(x)[i] = exp(log(-log(f64(x)[i])) / shape) / rate;
	}
	return x;
}

vec rcauchy(u64 n, f64 location, f64 scale) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] = location + scale * tan(M_PI * f64(x)[i]);
	}
	return x;
}

vec rlogis(u64 n, f64 location, f64 scale) {
	vec x = runif(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] = location + scale * log(f64(x)[i] / (1 - f64(x)[i]));
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
			x[i] -= log(f64(u)[j]);
		}
		x[i] /= rate;
		free(f64(u));
	}
	return (vec) {FLOAT, n, x};
}

vec rchisq(u64 n, u64 df) {
	f64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(df / 2, 0, 1);
		x[i] = 0;
		for (u64 j = 0; j < df / 2; j++) {
			x[i] -= log(f64(u)[j]);
		}
		x[i] *= 2;
		free(f64(u));
	}
	if (df % 2 == 1) {
		vec z = rnorm(n, 0, 1);
		for (u64 i = 0; i < n; i++) {
			x[i] += f64(z)[i] * f64(z)[i];
		}
		free(f64(z));
	}
	return (vec) {FLOAT, n, x};
}

vec rf(u64 n, u64 df1, u64 df2) {
	vec x = rchisq(n, df1);
	vec c = rchisq(n, df2);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] /= f64(c)[i] * df1 / df2;
	}
	return x;
}

vec rbeta(u64 n, u64 shape1, u64 shape2) {
	f64 *x = malloc(n * sizeof *x);
	for (u64 i = 0; i < n; i++) {
		vec u = runif(shape1 + shape2, 0, 1);
		f64 num = 0;
		for(u64 j = 0; j < shape1; j++) {
			num -= log(f64(u)[j]);
		}
		f64 den = num;
		for(u64 j = shape1; j < shape1 + shape2; j++) {
			den -= log(f64(u)[j]);
		}
		x[i] = num / den;
		free(f64(u));
	}
	return (vec) {FLOAT, n, x};
}

// Box Muller: Normal --------------------------------------------------------

vec rnorm(u64 n, f64 mean, f64 sd) {
	f64 *x = malloc(n * sizeof *x);
	vec u = runif(n + 1, 0, 1);
	for (u64 i = 0; i < n; i += 2) {
		f64 R = sd * sqrt(-2 * log(f64(u)[i]));
		f64 theta = 2 * M_PI * f64(u)[i + 1];
		x[i] = mean + R * sin(theta);
		if (i + 1 == n) break;
		x[i + 1] = mean + R * cos(theta);
	}
	return (vec) {FLOAT, n, x};
}

// Relation to Normal: Log normal, T -----------------------------------------

vec rlnorm(u64 n, f64 meanlog, f64 sdlog) {
	vec x = rnorm(n, meanlog, sdlog);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] = exp(f64(x)[i]);
	}
	return x;
}

vec rt(u64 n, u64 df) {
	if (df == 1) return rcauchy(n, 0, 1);
	vec x = rnorm(n, 0, 1);
	vec c = rchisq(n, df);
	for (u64 i = 0; i < n; i++) {
		f64(x)[i] *= sqrt(df / f64(c)[i]);
	}
	return x;
}

/*
 * Limitations: --------------------------------------------------------------
 * Poisson is O(n * lambda)
 * Binomial and Negative binomial are O(n * size)
 * No Hypergeometric
 * Gamma, Betam Chi-squared, F and t need integer shape and df parameters
 *     Gamma       O(n * shape)
 *     Beta        O(n * (shape1 + shape2))
 *     Chi-squared O(n * df)
 *     F           O(n * (df1 + df2))
 *     t           O(n * df)
 */
