#ifndef KEK_H_
#define KEK_H_

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>

#define M_PI 3.14159265358979323846

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
	u64 nrow;
	u64 ncol;
	s64 *colnames;
	vec *var;
} df;

vec vec_new(u64 n);
void vec_free(vec x);
vec vec_fill(u64 n, f64 value);
vec vec_seq(u64 n, f64 start, f64 by);
vec vec_combine(vec x, vec y);
vec vec_add(vec x, vec y);

u64 all(vec);
u64 any(vec);
vec which(vec x, s64 op, f64 value);

void rinit(u64 seed);
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

f64 sum(vec x);
f64 mean(vec x);
f64 var(vec x);
f64 sd(vec x);
f64 cov(vec x1, vec x2);
f64 cor(vec x1, vec x2);

void print_vec(vec x);
void print_df(df data);

df read_df(s64 path, u64 nrow, u64 ncol);

void write_vec(vec x, s64 path);

#endif // KEK_H_
