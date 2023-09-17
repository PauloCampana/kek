#include "../kek.h"

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
	f64 sum = 0, li = 1, gam = 1;
	for (u64 i = 0; i <= floor(x); i++) {
		sum += li / gam;
		li *= lambda;
		gam *= i + 1;
	}
	return exp(-lambda) * sum;
}

f64 pbinom(f64 x, u64 size, f64 prob) {
	if (x <  0) return 0;
	if (x >= size) return 1;
	return 1 - pbeta(prob, floor(x) + 1, size - floor(x));
}

f64 pnbinom(f64 x, u64 size, f64 prob) {
	if (x < 0) return 0;
	return pbeta(prob, size, floor(x) + 1);
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
	x *= rate;
	f64 sum = 0, xi = 1, gam = tgamma(shape + 1);
	for (u64 i = 0; i < 100; i++) {
		sum += xi / gam;
		xi *= x;
		gam *= shape + 1 + i;
	}
	f64 tmp = shape * log(x) - x + log(sum);
	return exp(tmp);
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
	f64 num, den, current = 0;
	for (u64 i = 15; i >= 1; i--) {
		u64 m = i / 2;
		if (i % 2 == 0) {
			num = m * (shape2 - m) * x;
			den = (shape1 + 2 * m - 1) * (shape1 + 2 * m);
		} else {
			num = -(shape1 + m) * (shape1 + shape2 + m) * x;
			den = (shape1 + 2 * m + 1) * (shape1 + 2 * m);
		}
		current = num / den / (1 + current);
	}
	f64 beta = lgamma(shape1) + lgamma(shape2) - lgamma(shape1 + shape2);
	f64 tmp = shape1 * log(x) + shape2 * log(1 - x) - beta;
	return exp(tmp) / shape1 / (1 + current);
}

f64 pnorm(f64 x, f64 mean, f64 sd) {
	x = (x - mean) / sd;
	return erfc(-x / M_SQRT2) / 2;
}

f64 plnorm(f64 x, f64 meanlog, f64 sdlog) {
	if (x <= 0) return 0;
	return pnorm(log(x), meanlog, sdlog);
}

f64 pt(f64 x, f64 df) {
	f64 den = df + x * x;
	f64 tmp = pbeta(df / den, df / 2, 0.5) / 2;
	return x <= 0 ? tmp : 1 - tmp;
}
