#include "prob.h"
#include <math.h>

f64 distribution_uniform(f64 x, f64 min, f64 max) {
	if (x <= min) return 0;
	if (x >= max) return 1;
	return (x - min) / (max - min);
}

f64 distribution_bernoulli(f64 x, f64 prob) {
	if (x <  0) return 0;
	if (x >= 1) return 1;
	return 1 - prob;
}

f64 distribution_geometric(f64 x, f64 prob) {
	if (x < 0) return 0;
	f64 p = (floor(x) + 1) * log(1 - prob);
	return -expm1(p);
}

f64 distribution_poisson(f64 x, f64 lambda) {
	if (x < 0) return 0;
	f64 sum = 0;
	f64 li = 1;
	f64 gam = 1;
	for (u64 i = 0; i <= floor(x); i++) {
		sum += li / gam;
		li *= lambda;
		gam *= i + 1;
	}
	return exp(-lambda) * sum;
}

f64 distribution_binomial(f64 x, u64 size, f64 prob) {
	if (x <  0) return 0;
	if (x >= size) return 1;
	return 1 - distribution_beta(prob, floor(x) + 1, size - floor(x));
}

f64 distribution_negative_binomial(f64 x, u64 size, f64 prob) {
	if (x < 0) return 0;
	return distribution_beta(prob, size, floor(x) + 1);
}

f64 distribution_exponential(f64 x, f64 rate) {
	if (x <= 0) return 0;
	return -expm1(-rate * x);
}

f64 distribution_weibull(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	return -expm1(-pow(rate * x, shape));
}

f64 distribution_cauchy(f64 x, f64 location, f64 scale) {
	x = (x - location) / scale;
	return atan(x) / M_PI + 0.5;
}

f64 distribution_logistic(f64 x, f64 location, f64 scale) {
	x = (x - location) / scale;
	return 1 / (exp(-x) + 1);
}

f64 distribution_gamma(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	x *= rate;
	f64 sum = 0;
	f64 xi = 1;
	f64 gam = tgamma(shape + 1);
	for (u64 i = 0; i < 100; i++) {
		sum += xi / gam;
		xi *= x;
		gam *= shape + 1 + i;
	}
	f64 tmp = shape * log(x) - x + log(sum);
	return exp(tmp);
}

f64 distribution_chi_squared(f64 x, f64 df) {
	return distribution_gamma(x, df / 2, 0.5);
}

f64 distribution_f(f64 x, f64 df1, f64 df2) {
	return distribution_beta(df1 * x / (df2 + df1 * x), df1 / 2, df2 / 2);
}

f64 distribution_beta(f64 x, f64 shape1, f64 shape2) {
	if (x <= 0) return 0;
	if (x >= 1) return 1;
	f64 current = 0;
	for (u64 i = 15; i >= 1; i--) {
		u64 m = i / 2;
		if (i % 2 == 0) {
			f64 num = m * (shape2 - m) * x;
			f64 den = (shape1 + 2 * m - 1) * (shape1 + 2 * m);
			current = num / den / (1 + current);
		} else {
			f64 num = -(shape1 + m) * (shape1 + shape2 + m) * x;
			f64 den = (shape1 + 2 * m + 1) * (shape1 + 2 * m);
			current = num / den / (1 + current);
		}
	}
	f64 beta = lgamma(shape1) + lgamma(shape2) - lgamma(shape1 + shape2);
	f64 tmp = shape1 * log(x) + shape2 * log(1 - x) - beta;
	return exp(tmp) / shape1 / (1 + current);
}

f64 distribution_normal(f64 x, f64 mean, f64 sd) {
	x = (x - mean) / sd;
	return erfc(-x / M_SQRT2) / 2;
}

f64 distribution_lognormal(f64 x, f64 meanlog, f64 sdlog) {
	if (x <= 0) return 0;
	return distribution_normal(log(x), meanlog, sdlog);
}

f64 distribution_t(f64 x, f64 df) {
	f64 den = df + x * x;
	f64 tmp = distribution_beta(df / den, df / 2, 0.5) / 2;
	return x <= 0 ? tmp : 1 - tmp;
}
