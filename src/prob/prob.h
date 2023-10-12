#pragma once

#include "../../kek.h"

f64 density_uniform(f64 x, f64 min, f64 max);
f64 density_bernoulli(f64 x, f64 prob);
f64 density_geommetric(f64 x, f64 prob);
f64 density_poisson(f64 x, f64 lambda);
f64 density_binomial(f64 x, u64 size, f64 prob);
f64 density_negative_binomial(f64 x, u64 size, f64 prob);
f64 density_exponential(f64 x, f64 rate);
f64 density_weibull(f64 x, f64 shape, f64 rate);
f64 density_cauchy(f64 x, f64 location, f64 scale);
f64 density_logistic(f64 x, f64 location, f64 scale);
f64 density_gamma(f64 x, f64 shape, f64 rate);
f64 density_chi_squared(f64 x, f64 df);
f64 density_f(f64 x, f64 df1, f64 df2);
f64 density_beta(f64 x, f64 shape1, f64 shape2);
f64 density_normal(f64 x, f64 mean, f64 sd);
f64 density_lognormal(f64 x, f64 meanlog, f64 sdlog);
f64 density_t(f64 x, f64 df);

f64 distribution_uniform(f64 x, f64 min, f64 max);
f64 distribution_bernoulli(f64 x, f64 prob);
f64 distribution_geometric(f64 x, f64 prob);
f64 distribution_poisson(f64 x, f64 lambda);
f64 distribution_binomial(f64 x, u64 size, f64 prob);
f64 distribution_negative_binomial(f64 x, u64 size, f64 prob);
f64 distribution_exponential(f64 x, f64 rate);
f64 distribution_weibull(f64 x, f64 shape, f64 rate);
f64 distribution_cauchy(f64 x, f64 location, f64 scale);
f64 distribution_logistic(f64 x, f64 location, f64 scale);
f64 distribution_gamma(f64 x, f64 shape, f64 rate);
f64 distribution_chi_squared(f64 x, f64 df);
f64 distribution_f(f64 x, f64 df1, f64 df2);
f64 distribution_beta(f64 x, f64 shape1, f64 shape2);
f64 distribution_normal(f64 x, f64 mean, f64 sd);
f64 distribution_lognormal(f64 x, f64 meanlog, f64 sdlog);
f64 distribution_t(f64 x, f64 df);

f64 quantile_uniform(f64 x, f64 min, f64 max);
f64 quantile_bernoulli(f64 x, f64 prob);
f64 quantile_geometric(f64 x, f64 prob);
f64 quantile_poisson(f64 x, f64 lambda);
f64 quantile_negative_binomial(f64 x, u64 size, f64 prob);
f64 quantile_negative_binomial(f64 x, u64 size, f64 prob);
f64 quantile_exponential(f64 x, f64 rate);
f64 quantile_weibull(f64 x, f64 shape, f64 rate);
f64 quantile_cauchy(f64 x, f64 location, f64 scale);
f64 quantile_logistic(f64 x, f64 location, f64 scale);
f64 quantile_gamma(f64 x, f64 shape, f64 rate);
f64 quantile_chi_squared(f64 x, f64 df);
f64 quantile_f(f64 x, f64 df1, f64 df2);
f64 quantile_beta(f64 x, f64 shape1, f64 shape2);
f64 quantile_normal(f64 x, f64 mean, f64 sd);
f64 quantile_lognormal(f64 x, f64 meanlog, f64 sdlog);
f64 quantile_t(f64 x, f64 df);
