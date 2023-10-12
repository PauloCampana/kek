#pragma once

#include "../../kek.h"

vec vec_new(u64 n);
vec vec_copy(vec x);
void vec_free(vec x);
vec vec_fill(u64 n, f64 value);
vec vec_seq(u64 n, f64 start, f64 by);
vec vec_rep(vec x, u64 times, u64 each);
vec vec_unique(vec x);
vec vec_combine(vec x, vec y);
vec vec_sort(vec x);
vec vec_reverse(vec x);
vec vec_accumulate(vec x);
u64 vec_all(vec);
u64 vec_any(vec);
f64 vec_min(vec x);
f64 vec_max(vec x);
vec vec_in(vec x, vec y);
vec vec_which(vec x, s64 op, f64 value);
vec vec_filter(vec x, s64 op, f64 value);

vec vec_apply1(vec x, f64 fun(f64));
vec vec_apply2(vec x, vec y, f64 fun(f64, f64));
vec vec_apply3(vec x, vec y, vec z, f64 fun(f64, f64, f64));
vec vec_standardize(vec x);
vec vec_add(vec x, vec y);
vec vec_subtract(vec x, vec y);
vec vec_multiply(vec x, vec y);
vec vec_divide(vec x, vec y);
vec vec_round(vec x);
vec vec_floor(vec x);
vec vec_ceiling(vec x);
vec vec_truncate(vec x);

mat mat_new(u64 nrow, u64 ncol);
mat mat_copy(mat x);
void mat_free(mat x);
vec mat_vec(mat x, s64 name);
mat mat_transpose(mat x);
mat mat_multiply(mat x, mat y);
mat mat_submat(mat x, vec rows, vec cols);
f64 mat_determinant(mat x);
mat mat_inverse(mat x);
