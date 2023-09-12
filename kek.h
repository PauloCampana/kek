#ifndef KEK_H_
#define KEK_H_

#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define M_PI 3.14159265358979323846

enum {
    VOID = 0,
    INTEGER = 1,
    UNSIGNED = 2,
    FLOAT = 3,
    CHAR = 4,
    STRING = 5
};

typedef void                   v64;
typedef signed   long long int i64;
typedef unsigned long long int u64;
typedef double                 f64;
typedef char                   c64;
typedef char *                 s64;

#define v64(vec) ((v64 *) vec.x)
#define i64(vec) ((i64 *) vec.x)
#define u64(vec) ((u64 *) vec.x)
#define f64(vec) ((f64 *) vec.x)
#define c64(vec) ((c64 *) vec.x)
#define s64(vec) ((s64 *) vec.x)

typedef struct {
    u64 type;
    u64 len;
    void *x;
} vec;

typedef struct {
    u64 nrow;
    u64 ncol;
    vec colnames;
    vec *var;
} df;

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
f64 sumprod(vec x1, vec x2);
f64 var(vec x);
f64 sd(vec x);
f64 cov(vec x1, vec x2);
f64 cor(vec x1, vec x2);

void print_vec(vec x);
void print_df(df data);

df read_df(char *path, u64 nrow, u64 ncol, char *colspec);

void write_vec(vec x, char *path);

#endif // KEK_H_
