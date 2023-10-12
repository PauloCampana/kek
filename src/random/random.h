#pragma once

#include "../../kek.h"

void rinit(u64 seed);
void rjump(void);
vec sample(vec x, u64 size, u64 replacement);
vec runif(u64 n, f64 min, f64 max);
vec rber(u64 n, f64 prob);
vec rgeom(u64 n, f64 prob);
vec rpois(u64 n, f64 lambda);
vec rbinom(u64 n, u64 size, f64 prob);
vec rnbinom(u64 n, u64 size, f64 prob);
vec rexp(u64 n, f64 rate);
vec rweibull(u64 n, f64 shape, f64 rate);
vec rcauchy(u64 n, f64 location, f64 scale);
vec rlogis(u64 n, f64 location, f64 scale);
vec rgamma(u64 n, f64 shape, f64 rate);
vec rchisq(u64 n, f64 df);
vec rf(u64 n, f64 df1, f64 df2);
vec rbeta(u64 n, f64 shape1, f64 shape2);
vec rnorm(u64 n, f64 mean, f64 sd);
vec rlnorm(u64 n, f64 meanlog, f64 sdlog);
vec rt(u64 n, f64 df);
