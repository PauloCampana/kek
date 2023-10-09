#include "../kek.h"
#include <math.h>

f64 qunif(f64 x, f64 min, f64 max) {
	if (x < 0 || x > 1) return NAN;
	return min + (max - min) * x;
}

f64 qber(f64 x, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x <= 1 - prob + 1e-15) return 0;
	return 1;
}

f64 qgeom(f64 x, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x < prob) return 0;
	return ceil(log(1 - x) / log1p(-prob) - 1);
}

f64 qpois(f64 x, f64 lambda) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += dpois(i, lambda);
		if (sum > x) return i;
	}
}

f64 qbinom(f64 x, u64 size, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return size;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += dbinom(i, size, prob);
		if (sum > x) return i;
	}
}

f64 qnbinom(f64 x, u64 size, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += dnbinom(i, size, prob);
		if (sum > x) return i;
	}
}

f64 qexp(f64 x, f64 rate) {
	if (x < 0 || x > 1) return NAN;
	return log(1 - x) / -rate;
}

f64 qweibull(f64 x, f64 shape, f64 rate) {
	if (x < 0 || x > 1) return NAN;
	return pow(-log(1 - x), 1 / shape) / rate;
}

f64 qcauchy(f64 x, f64 location, f64 scale) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	if (x == 0) return -INFINITY;
	return location + scale * tan(M_PI * (x - 0.5));
}

f64 qlogis(f64 x, f64 location, f64 scale) {
	if (x < 0 || x > 1) return NAN;
	return location + scale * log(x / (1 - x));
}

f64 qgamma(f64 x, f64 shape, f64 rate);
f64 qchisq(f64 x, f64 df);
f64 qf(f64 x, f64 df1, f64 df2);
f64 qbeta(f64 x, f64 shape1, f64 shape2);

f64 qnorm(f64 x, f64 mean, f64 sd) {
	if (x < 0 || x > 1) return NAN;
	x = 1 - 2 * x;
	f64 sgn = fabs(x) / x;
	f64 tmp1 = log(1 - x * x);
	f64 tmp2 = 2 / (M_PI * 0.147) + tmp1 / 2;
	f64 tmp3 = sgn * sqrt(sqrt(tmp2 * tmp2 - tmp1 / 0.147) - tmp2);
	return mean - sd * M_SQRT2 * tmp3;
}

f64 qlnorm(f64 x, f64 meanlog, f64 sdlog) {
	return exp(qnorm(x, meanlog, sdlog));
}

f64 qt(f64 x, f64 df);
