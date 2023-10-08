#include "../kek.h"
#include <math.h>

f64 dunif(f64 x, f64 min, f64 max) {
	if (x < min || x > max) return 0;
	return 1 / (max - min);
}

f64 dber(f64 x, f64 prob) {
	if (x == 1) return prob;
	if (x == 0) return 1 - prob;
	return 0;
}

f64 dgeom(f64 x, f64 prob) {
	if (x < 0 || x != round(x)) return 0;
	return prob * pow((1 - prob), x);
}

f64 dpois(f64 x, f64 lambda) {
	if (x < 0 || x != round(x)) return 0;
	f64 d = -lambda + x * log(lambda) - lgamma(x + 1);
	return exp(d);
}

f64 dbinom(f64 x, u64 size, f64 prob) {
	if (x < 0 || x > size || x != round(x)) return 0;
	f64 binom = lgamma(size + 1) - lgamma(x + 1) - lgamma(size - x + 1);
	f64 d = binom + x * log(prob) + (size - x) * log(1 - prob);
	return exp(d);
}

f64 dnbinom(f64 x, u64 size, f64 prob) {
	if (x < 0 || x != round(x)) return 0;
	f64 binom = lgamma(size + x) - lgamma(size) - lgamma(x + 1);
	f64 d = binom + size * log(prob) + x * log(1 - prob);
	return exp(d);
}

f64 dexp(f64 x, f64 rate) {
	if (x < 0) return 0;
	return rate * exp(-rate * x);
}

f64 dweibull(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	f64 tmp1 = pow(rate * x, shape - 1);
	f64 tmp2 = tmp1 * rate * x;
	return shape * rate * exp(-tmp2) * tmp1;
}

f64 dcauchy(f64 x, f64 location, f64 scale) {
	x = (x - location) / scale;
	return 1 / (M_PI * scale * (1 + x * x));
}

f64 dlogis(f64 x, f64 location, f64 scale) {
	x = fabs(x - location) / scale;
	f64 tmp1 = exp(-x);
	f64 tmp2 = tmp1 + 1;
	return tmp1 / (scale * tmp2 * tmp2);
}

f64 dgamma(f64 x, f64 shape, f64 rate) {
	if (x <= 0) return 0;
	f64 tmp1 = shape * log(rate) - lgamma(shape);
	f64 tmp2 = (shape - 1) * log(x) - rate * x;
	return exp(tmp1 + tmp2);
}

f64 dchisq(f64 x, f64 df) {
	return dgamma(x, df / 2, 0.5);
}

f64 df(f64 x, f64 df1, f64 df2) {
	if (x <= 0) return 0;
	f64 df3 = df1 / 2;
	f64 df4 = df2 / 2;
	f64 df5 = df3 + df4;
	f64 tmp1 = df3 * log(df1) + df4 * log(df2) + (df3 - 1) * log(x);
	f64 tmp2 = -df5 * log(df2 + df1 * x);
	f64 tmp3 = lgamma(df3) + lgamma(df4) - lgamma(df5);
	return exp(tmp1 + tmp2 - tmp3);
}

f64 dbeta(f64 x, f64 shape1, f64 shape2) {
	if (x <= 0 || x >= 1) return 0;
	f64 tmp1 = (shape1 - 1) * log(x) + (shape2 - 1) * log1p(-x);
	f64 tmp2 = lgamma(shape1) + lgamma(shape2) - lgamma(shape1 + shape2);
	return exp(tmp1 - tmp2);
}

f64 dnorm(f64 x, f64 mean, f64 sd) {
	x = (x - mean) / sd;
	return exp(-0.5 * x * x) / (sd * M_SQRT2PI);
}

f64 dlnorm(f64 x, f64 meanlog, f64 sdlog) {
	if (x <= 0) return 0;
	f64 z = (log(x) - meanlog) / sdlog;
	return exp(-0.5 * z * z) / (x * sdlog * M_SQRT2PI);
}

f64 dt(f64 x, f64 df) {
	f64 tmp1 = (df + 1) / 2 * log(df / (df + x * x)) - 0.5 * log(df);
	f64 tmp2 = lgamma(df / 2) + lgamma(0.5) - lgamma((df + 1) / 2);
	return exp(tmp1 - tmp2);
}
