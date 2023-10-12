#include "random.h"
#include <math.h>
#include <stdlib.h>

vec random_uniform(u64 n, f64 min, f64 max) {
	random_seed(0);
	vec uniform = vec_new(n);
	for (u64 i = 0; i < n; i++) {
		uniform.x[i] = min + (max - min) * random_f64();
	}
	return uniform;
}

vec random_bernoulli(u64 n, f64 prob) {
	vec bernoulli = random_uniform(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		bernoulli.x[i] = bernoulli.x[i] < prob;
	}
	return bernoulli;
}

vec random_geometric(u64 n, f64 prob) {
	vec geometric = random_uniform(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		geometric.x[i] = floor(log(geometric.x[i]) / log1p(-prob));
	}
	return geometric;
}

vec random_poisson(u64 n, f64 lambda) {
	vec poisson = vec_new(n);
	vec uniform = random_uniform(n, 0, 1);
	f64 p0 = exp(-lambda);
	for (u64 i = 0; i < n; i++) {
		f64 p = p0;
		f64 F = p;
		u64 j = 0;
		for (j = 0; uniform.x[i] >= F; j++) {
			p *= lambda / (j + 1);
			F += p;
		}
		poisson.x[i] = j;
	}
	return poisson;
}

vec random_binomial(u64 n, u64 size, f64 prob) {
	random_seed(0);
	vec binomial = vec_new(n);
	for (u64 i = 0; i < n; i++) {
		binomial.x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			binomial.x[i] += random_f64() < prob;
		}
	}
	return binomial;
}

vec random_negative_binomial(u64 n, u64 size, f64 prob) {
	random_seed(0);
	vec negative_binomial = vec_new(n);
	for (u64 i = 0; i < n; i++) {
		negative_binomial.x[i] = 0;
		for (u64 j = 0; j < size; j++) {
			f64 random = random_f64();
			f64 geometric = floor(log(random) / log1p(-prob));
			negative_binomial.x[i] += geometric;
		}
	}
	return negative_binomial;
}

vec random_exponential(u64 n, f64 rate) {
	vec exponential = random_uniform(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		exponential.x[i] = log(exponential.x[i]) / -rate;
	};
	return exponential;
}

vec random_weibull(u64 n, f64 shape, f64 rate) {
	vec weibull = random_uniform(n, 0, 1);
	f64 invshape = 1 / shape;
	for (u64 i = 0; i < n; i++) {
		weibull.x[i] = pow(-log(weibull.x[i]), invshape) / rate;
	}
	return weibull;
}

vec random_cauchy(u64 n, f64 location, f64 scale) {
	vec cauchy = random_uniform(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		cauchy.x[i] = location + scale * tan(M_PI * cauchy.x[i]);
	}
	return cauchy;
}

vec random_logistic(u64 n, f64 location, f64 scale) {
	vec logistic = random_uniform(n, 0, 1);
	for (u64 i = 0; i < n; i++) {
		f64 tmp = log(logistic.x[i] / (1 - logistic.x[i]));
		logistic.x[i] = location + scale * tmp;
	}
	return logistic;
}

vec random_chi_squared(u64 n, f64 df) {
	return random_gamma(n, df / 2, 0.5);
}

vec random_f(u64 n, f64 df1, f64 df2) {
	vec f = random_chi_squared(n, df1);
	vec chi_squared = random_chi_squared(n, df2);
	f64 ratio = df1 / df2;
	for (u64 i = 0; i < n; i++) {
		f.x[i] /= chi_squared.x[i] * ratio;
	}
	vec_free(chi_squared);
	return f;
}

vec random_beta(u64 n, f64 shape1, f64 shape2) {
	vec beta = random_gamma(n, shape1, 1);
	vec gamma = random_gamma(n, shape2, 1);
	for (u64 i = 0; i < n; i++) {
		beta.x[i] /= beta.x[i] + gamma.x[i];
	}
	vec_free(gamma);
	return beta;
}

vec random_lognormal(u64 n, f64 meanlog, f64 sdlog) {
	vec lognormal = random_normal(n, meanlog, sdlog);
	for (u64 i = 0; i < n; i++) {
		lognormal.x[i] = exp(lognormal.x[i]);
	}
	return lognormal;
}

vec random_t(u64 n, f64 df) {
	vec t = random_normal(n, 0, 1);
	vec chi_squared = random_chi_squared(n, df);
	for (u64 i = 0; i < n; i++) {
		t.x[i] *= sqrt(df / chi_squared.x[i]);
	}
	vec_free(chi_squared);
	return t;
}
