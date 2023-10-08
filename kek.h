#pragma once

#include <stdio.h>

#define M_PI      3.14159265358979323846
#define M_SQRT2   1.41421356237309504880
#define M_SQRT2PI 2.50662827463100050241

typedef signed   long long int i64;
typedef unsigned long long int u64;
typedef double                 f64;
typedef char                   c64;
typedef char *                 s64;

typedef struct {
	u64 len;
	f64 *x;
} vec;

typedef struct {
	u64 len;
	c64 (*colnames)[64];
	c64 (*rownames)[64];
	vec *x;
} mat;

typedef struct {
	mat x;
	mat y;
	mat coefficients;
} reg;

vec vec_new(u64 n);
vec vec_copy(vec x);
void vec_free(vec x);
vec vec_fill(u64 n, f64 value);
vec vec_seq(u64 n, f64 start, f64 by);
vec vec_combine(vec x, vec y);
vec vec_sort(vec x);
vec vec_accumulate(vec x);
u64 vec_all(vec);
u64 vec_any(vec);
vec vec_which(vec x, s64 op, f64 value);
vec vec_add(vec x, vec y);
vec vec_subtract(vec x, vec y);
vec vec_multiply(vec x, vec y);
vec vec_divide(vec x, vec y);

mat mat_new(u64 nrow, u64 ncol);
mat mat_copy(mat x);
void mat_free(mat x);
vec mat_vec(mat x, s64 name);
mat mat_transpose(mat x);
mat mat_multiply(mat x, mat y);
mat mat_submat(mat x, vec rows, vec cols);
f64 mat_determinant(mat x);
mat mat_inverse(mat x);

reg reg_linear(mat data, s64 dep);
vec reg_predictions(reg fit);
vec reg_residuals(reg fit);
vec reg_residuals_norm(reg fit);
f64 reg_rmse(reg fit);

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
vec rgamma(u64 n, u64 shape, f64 rate);
vec rchisq(u64 n, u64 df);
vec rf(u64 n, u64 df1, u64 df2);
vec rbeta(u64 n, u64 shape1, u64 shape2);
vec rnorm(u64 n, f64 mean, f64 sd);
vec rlnorm(u64 n, f64 meanlog, f64 sdlog);
vec rt(u64 n, u64 df);

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
f64 dF(f64 x, f64 df1, f64 df2);
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
f64 pF(f64 x, f64 df1, f64 df2);
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
f64 qF(f64 x, f64 df1, f64 df2);
f64 qbeta(f64 x, f64 shape1, f64 shape2);
f64 qnorm(f64 x, f64 mean, f64 sd);
f64 qlnorm(f64 x, f64 meanlog, f64 sdlog);
f64 qt(f64 x, f64 df);

f64 sum(vec x);
f64 mean(vec x);
f64 var(vec x);
f64 sd(vec x);
f64 cov(vec x1, vec x2);
f64 cor(vec x1, vec x2);

void print_vec_(vec x, s64 name);
#define print_vec(x) print_vec_(x, #x);
void print_mat_(mat x, s64 name);
#define print_mat(x) print_mat_(x, #x);

mat read_mat(s64 path);

void write_vec(vec x, s64 path);
void write_vec_dat(vec x, s64 path);
void write_mat(mat x, s64 path);
