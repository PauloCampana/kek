#pragma once

#include "../../kek.h"

void random_seed(u64 seed);
void random_jump(void);

u64 random_u64(void);
f64 random_f64(void);
f64 random_normal_single(void);

vec random_sample(vec x, u64 size, u64 replacement);

vec random_uniform(u64 n, f64 min, f64 max);
vec random_bernoulli(u64 n, f64 prob);
vec random_geometric(u64 n, f64 prob);
vec random_poisson(u64 n, f64 lambda);
vec random_binomial(u64 n, u64 size, f64 prob);
vec random_negative_binomial(u64 n, u64 size, f64 prob);
vec random_exponential(u64 n, f64 rate);
vec random_weibull(u64 n, f64 shape, f64 rate);
vec random_cauchy(u64 n, f64 location, f64 scale);
vec random_logistic(u64 n, f64 location, f64 scale);
vec random_gamma(u64 n, f64 shape, f64 rate);
vec random_chi_squared(u64 n, f64 df);
vec random_f(u64 n, f64 df1, f64 df2);
vec random_beta(u64 n, f64 shape1, f64 shape2);
vec random_normal(u64 n, f64 mean, f64 sd);
vec random_lognormal(u64 n, f64 meanlog, f64 sdlog);
vec random_t(u64 n, f64 df);

