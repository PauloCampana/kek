#include "../kek.h"
#include <math.h>

f64 punif(f64 x, f64 min, f64 max) {
	if (x <= min) return 0;
	if (x >= max) return 1;
	return (x - min) / (max - min);
}

f64 pber(f64 x, f64 prob) {
	if (x <  0) return 0;
	if (x >= 1) return 1;
	return 1 - prob;
}

f64 pgeom(f64 x, f64 prob) {
	if (x < 0) return 0;
	f64 p = (floor(x) + 1) * log(1 - prob);
	return -expm1(p);
}

f64 ppois(f64 x, f64 lambda) {
	if (x < 0) return 0;
	f64 sum = 0;
	for (u64 i = 0; i <= floor(x); i++) {
		sum += dpois(i, lambda);
	}
	// return pgamma(lambda, floor(x) + 1, 1)
	return sum;
}

f64 pbinom(f64 x, u64 size, f64 prob) {
	if (x <  0) return 0;
	if (x >= size) return 1;
	f64 sum = 0;
	for (u64 i = 0; i <= floor(x); i++) {
		sum += dbinom(i, size, prob);
	}
	// return pbeta(prob, floor(x) + 1, size - x);
	return sum;
}

f64 pnbinom(f64 x, u64 size, f64 prob) {
	if (x < 0) return 0;
	f64 sum = 0;
	for (u64 i = 0; i <= floor(x); i++) {
		sum += dnbinom(i, size, prob);
	}
	// return pbeta(prob, size, floor(x) + 1);
	return sum;
}

f64 pexp(f64 x, f64 rate) {
	if (x <= 0) return 0;
	return -expm1(-rate * x);
}

f64 pweibull(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	return -expm1(-pow(rate * x, shape));
}

f64 pcauchy(f64 x, f64 location, f64 scale) {
	x = (x - location) / scale;
	return atan(x) / M_PI + 0.5;
}

f64 plogis(f64 x, f64 location, f64 scale) {
	x = (x - location) / scale;
	return 1 / (exp(-x) + 1);
}

f64 pgamma(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	(void) shape; (void) rate;
	// TODO
	return 0;
}

f64 pchisq(f64 x, f64 df) {
	return pgamma(x, df / 2, 0.5);
}

f64 pF(f64 x, f64 df1, f64 df2) {
	return pbeta(df1 * x / (df2 + df1 * x), df1 / 2, df2 / 2);
}

f64 pbeta(f64 x, f64 shape1, f64 shape2) {
	if (x <= 0) return 0;
	if (x >= 1) return 1;
	(void) shape1; (void) shape2;
	// TODO
	return 0;
}

f64 pnorm(f64 x, f64 mean, f64 sd) {
	x = (x - mean) / sd;
	return 0.5 * erfc(-x / M_SQRT2);
}

f64 plnorm(f64 x, f64 meanlog, f64 sdlog) {
	if (x <= 0) return 0;
	return pnorm(log(x), meanlog, sdlog);
}

f64 pt(f64 x, f64 df) {
	(void) x; (void) df;
	// TODO
	return 0;
}
