#include "prob.h"
#include <math.h>

f64 quantile_uniform(f64 x, f64 min, f64 max) {
	if (x < 0 || x > 1) return NAN;
	return min + (max - min) * x;
}

f64 quantile_bernoulli(f64 x, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x <= 1 - prob + 1e-15) return 0;
	return 1;
}

f64 quantile_geometric(f64 x, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x < prob) return 0;
	return ceil(log(1 - x) / log1p(-prob) - 1);
}

f64 quantile_poisson(f64 x, f64 lambda) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += density_poisson(i, lambda);
		if (sum > x) return i;
	}
}

f64 quantile_binomial(f64 x, u64 size, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return size;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += density_binomial(i, size, prob);
		if (sum > x) return i;
	}
}

f64 quantile_negative_binomial(f64 x, u64 size, f64 prob) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	f64 sum = 0;
	for (u64 i = 0; ; i++) {
		sum += density_negative_binomial(i, size, prob);
		if (sum > x) return i;
	}
}

f64 quantile_exponential(f64 x, f64 rate) {
	if (x < 0 || x > 1) return NAN;
	return log(1 - x) / -rate;
}

f64 quantile_weibull(f64 x, f64 shape, f64 rate) {
	if (x < 0 || x > 1) return NAN;
	return pow(-log(1 - x), 1 / shape) / rate;
}

f64 quantile_cauchy(f64 x, f64 location, f64 scale) {
	if (x < 0 || x > 1) return NAN;
	if (x == 1) return INFINITY;
	if (x == 0) return -INFINITY;
	return location + scale * tan(M_PI * (x - 0.5));
}

f64 quantile_logistic(f64 x, f64 location, f64 scale) {
	if (x < 0 || x > 1) return NAN;
	return location + scale * log(x / (1 - x));
}

f64 quantile_gamma(f64 x, f64 shape, f64 rate);
f64 quantile_chi_squared(f64 x, f64 df);
f64 quantile_f(f64 x, f64 df1, f64 df2);
f64 quantile_beta(f64 x, f64 shape1, f64 shape2);

f64 quantile_normal(f64 x, f64 mean, f64 sd) {
	if (x < 0 || x > 1) return NAN;
	x = 1 - 2 * x;
	f64 sgn = fabs(x) / x;
	f64 tmp1 = log(1 - x * x);
	f64 tmp2 = 2 / (M_PI * 0.147) + tmp1 / 2;
	f64 tmp3 = sgn * sqrt(sqrt(tmp2 * tmp2 - tmp1 / 0.147) - tmp2);
	return mean - sd * M_SQRT2 * tmp3;
}

f64 quantile_lognormal(f64 x, f64 meanlog, f64 sdlog) {
	return exp(quantile_normal(x, meanlog, sdlog));
}

f64 quantile_t(f64 x, f64 df);
