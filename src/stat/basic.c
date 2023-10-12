#include "stat.h"
#include <math.h>
#include <string.h>

f64 vec_sum(vec x) {
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		sum += x.x[i];
	}
	return sum;
}

f64 vec_mean(vec x) {
	return vec_sum(x) / x.len;
}

f64 vec_var(vec x) {
	f64 xbar = vec_mean(x);
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		sum += x.x[i] * x.x[i];
	}
	return (sum - x.len * xbar * xbar) / (x.len - 1);
}

f64 vec_sd(vec x) {
	return sqrt(vec_var(x));
}

f64 vec_cov(vec x1, vec x2) {
	f64 xbar1 = vec_mean(x1);
	f64 xbar2 = vec_mean(x2);
	f64 sum = 0;
	for (u64 i = 0; i < x1.len; i++) {
		sum += x1.x[i] * x2.x[i];
	}
	return (sum - x1.len * xbar1 * xbar2) / (x1.len - 1);
}

f64 vec_cor(vec x1, vec x2) {
	f64 xbar1 = vec_mean(x1);
	f64 xbar2 = vec_mean(x2);
	f64 sumxy = 0;
	f64 sumxx = 0;
	f64 sumyy = 0;
	for (u64 i = 0; i < x1.len; i++) {
		sumxy += x1.x[i] * x2.x[i];
		sumxx += x1.x[i] * x1.x[i];
		sumyy += x2.x[i] * x2.x[i];
	}
	f64 num  = sumxy - x1.len * xbar1 * xbar2;
	f64 den1 = sumxx - x1.len * xbar1 * xbar1;
	f64 den2 = sumyy - x2.len * xbar2 * xbar2;
	return num / sqrt(den1 * den2);
}

f64 vec_skewness(vec x) {
	f64 xbar = vec_mean(x);
	f64 sd = vec_sd(x);
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		f64 m0 = x.x[i] - xbar;
		sum += m0 * m0 * m0;
	}
	return sum / (x.len * sd * sd * sd);
}

f64 vec_kutrosis(vec x) {
	f64 xbar = vec_mean(x);
	f64 sumsq = 0;
	f64 sumfo = 0;
	for (u64 i = 0; i < x.len; i++) {
		f64 m0 = x.x[i] - xbar;
		f64 m02 = m0 * m0;
		sumsq += m02;
		sumfo += m02 * m02;
	}
	return x.len * sumfo / (sumsq * sumsq);
}

vec mat_col_sum(mat x) {
	vec sum = vec_new(x.len);
	for (u64 j = 0; j < x.len; j++) {
		sum.x[j] = vec_sum(x.x[j]);
	}
	return sum;
}

vec mat_col_mean(mat x) {
	vec mean = vec_new(x.len);
	for (u64 j = 0; j < x.len; j++) {
		mean.x[j] = vec_sum(x.x[j]) / x.x->len;
	}
	return mean;
}

vec mat_col_var(mat x) {
	vec var = vec_new(x.len);
	for (u64 j = 0; j < x.len; j++) {
		var.x[j] = vec_var(x.x[j]);
	}
	return var;
}

vec mat_col_sd(mat x) {
	vec sd = vec_new(x.len);
	for (u64 j = 0; j < x.len; j++) {
		sd.x[j] = vec_sd(x.x[j]);
	}
	return sd;
}

mat mat_cov(mat x) {
	mat cov = mat_new(x.len, x.len);
	for (u64 j = 0; j < x.len; j++) {
		strncpy(cov.colnames[j], x.colnames[j], sizeof cov.colnames[0]);
		strncpy(cov.rownames[j], x.colnames[j], sizeof cov.rownames[0]);
		cov.x[j].x[j] = vec_var(x.x[j]);
		for (u64 i = j + 1; i < x.len; i++) {
			f64 tmp = vec_cov(x.x[i], x.x[j]);
			cov.x[j].x[i] = tmp;
			cov.x[i].x[j] = tmp;
		}
	}
	return cov;
}

mat mat_cor(mat x) {
	mat cor = mat_new(x.len, x.len);
	for (u64 j = 0; j < x.len; j++) {
		strncpy(cor.colnames[j], x.colnames[j], sizeof cor.colnames[0]);
		strncpy(cor.rownames[j], x.colnames[j], sizeof cor.rownames[0]);
		cor.x[j].x[j] = 1;
		for (u64 i = j + 1; i < x.len; i++) {
			f64 tmp = vec_cor(x.x[i], x.x[j]);
			cor.x[j].x[i] = tmp;
			cor.x[i].x[j] = tmp;
		}
	}
	return cor;
}
