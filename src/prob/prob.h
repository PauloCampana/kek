#pragma once

#include "../../kek.h"

f64 dunif(f64 x, f64 min, f64 max);
f64 dber(f64 x, f64 prob);
f64 dgeom(f64 x, f64 prob);
f64 dpois(f64 x, f64 lambda);
f64 dbinom(f64 x, u64 size, f64 prob);
f64 dnbinom(f64 x, u64 size, f64 prob);
f64 dexp(f64 x, f64 rate);
f64 dweibull(f64 x, f64 shape, f64 rate);
f64 dcauchy(f64 x, f64 location, f64 scale);
f64 dlogis(f64 x, f64 location, f64 scale);
f64 dgamma(f64 x, f64 shape, f64 rate);
f64 dchisq(f64 x, f64 df);
f64 df(f64 x, f64 df1, f64 df2);
f64 dbeta(f64 x, f64 shape1, f64 shape2);
f64 dnorm(f64 x, f64 mean, f64 sd);
f64 dlnorm(f64 x, f64 meanlog, f64 sdlog);
f64 dt(f64 x, f64 df);

f64 punif(f64 x, f64 min, f64 max);
f64 pber(f64 x, f64 prob);
f64 pgeom(f64 x, f64 prob);
f64 ppois(f64 x, f64 lambda);
f64 pbinom(f64 x, u64 size, f64 prob);
f64 pnbinom(f64 x, u64 size, f64 prob);
f64 pexp(f64 x, f64 rate);
f64 pweibull(f64 x, f64 shape, f64 rate);
f64 pcauchy(f64 x, f64 location, f64 scale);
f64 plogis(f64 x, f64 location, f64 scale);
f64 pgamma(f64 x, f64 shape, f64 rate);
f64 pchisq(f64 x, f64 df);
f64 pf(f64 x, f64 df1, f64 df2);
f64 pbeta(f64 x, f64 shape1, f64 shape2);
f64 pnorm(f64 x, f64 mean, f64 sd);
f64 plnorm(f64 x, f64 meanlog, f64 sdlog);
f64 pt(f64 x, f64 df);

f64 qunif(f64 x, f64 min, f64 max);
f64 qber(f64 x, f64 prob);
f64 qgeom(f64 x, f64 prob);
f64 qpois(f64 x, f64 lambda);
f64 qbinom(f64 x, u64 size, f64 prob);
f64 qnbinom(f64 x, u64 size, f64 prob);
f64 qexp(f64 x, f64 rate);
f64 qweibull(f64 x, f64 shape, f64 rate);
f64 qcauchy(f64 x, f64 location, f64 scale);
f64 qlogis(f64 x, f64 location, f64 scale);
f64 qgamma(f64 x, f64 shape, f64 rate);
f64 qchisq(f64 x, f64 df);
f64 qf(f64 x, f64 df1, f64 df2);
f64 qbeta(f64 x, f64 shape1, f64 shape2);
f64 qnorm(f64 x, f64 mean, f64 sd);
f64 qlnorm(f64 x, f64 meanlog, f64 sdlog);
f64 qt(f64 x, f64 df);
