#pragma once

#define M_PI      3.14159265358979323846
#define M_SQRT2   1.41421356237309504880
#define M_SQRT2PI 2.50662827463100050241

typedef signed   long long int i64;
typedef unsigned long long int u64;
typedef double                 f64;
typedef char                   c64[64];
typedef char *                 s64;

typedef struct {
	u64 len;
	f64 *x;
} vec;

typedef struct {
	u64 len;
	c64 *colnames;
	c64 *rownames;
	vec *x;
} mat;

typedef struct {
	mat x;
	mat y;
	mat coefficients;
} reg;

#include "src/io/io.h"
#include "src/prob/prob.h"
#include "src/random/random.h"
#include "src/stat/stat.h"
#include "src/types/types.h"
