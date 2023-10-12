#pragma once

#include "../../kek.h"

f64 vec_sum(vec x);
f64 vec_mean(vec x);
f64 vec_var(vec x);
f64 vec_sd(vec x);
f64 vec_skewness(vec x);
f64 vec_kurtosis(vec x);
f64 vec_cov(vec x1, vec x2);
f64 vec_cor(vec x1, vec x2);

vec mat_col_sum(mat x);
vec mat_col_mean(mat x);
vec mat_col_var(mat x);
vec mat_col_sd(mat x);
vec mat_col_skewness(mat x);
vec mat_col_kurtosis(mat x);
mat mat_cov(mat x);
mat mat_cor(mat x);

reg reg_linear(mat data, s64 dep);
vec reg_predictions(reg fit);
vec reg_residuals(reg fit);
vec reg_residuals_norm(reg fit);
f64 reg_rmse(reg fit);
