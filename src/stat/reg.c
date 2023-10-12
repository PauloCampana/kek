#include "stat.h"
#include <math.h>
#include <string.h>

reg reg_linear(mat data, s64 dep) {
	u64 n = data.x->len;
	u64 p = data.len;
	u64 ycol = 0;
	for (u64 j = 0; j < p; j++) {
		u64 cmp = strcmp(data.colnames[j], dep);
		if (cmp == 0) ycol = j;
	}
	vec rows = vec_seq(n, 0, 1);
	vec colsy = (vec) {1, (f64[1]) {ycol}};
	vec colsx = vec_new(p - 1);
	for (u64 j = 0, tmp = 0; j < p; j++, tmp++) {
		if (tmp == ycol) tmp++;
		colsx.x[j] = tmp;
	}
	mat y = mat_submat(data, rows, colsy);
	mat tmp = mat_submat(data, rows, colsx);
	mat x = mat_new(n, p);
	for (u64 j = 0; j < p - 1; j++) {
		x.x[j + 1] = vec_copy(tmp.x[j]);
		strncpy(x.colnames[j + 1], tmp.colnames[j], sizeof x.colnames[0]);
	}
	for (u64 i = 0; i < rows.len; i++) {
		strncpy(x.rownames[i], tmp.rownames[i], sizeof x.rownames[0]);
	}
	x.x[0] = vec_fill(n, 1);
	strncpy(x.colnames[0], "intercept", sizeof x.colnames[0]);
	mat_free(tmp);
	vec_free(rows);
	vec_free(colsx);
	mat coefficients = mat_multiply(
		mat_inverse(mat_multiply(mat_transpose(x), x)),
		mat_multiply(mat_transpose(x), y)
	);
	return (reg) {x, y, coefficients};
}

vec reg_predictions(reg fit) {
	mat m = mat_multiply(fit.x, fit.coefficients);
	vec p = vec_copy(m.x[0]);
	mat_free(m);
	return p;
}

vec reg_residuals(reg fit) {
	vec p = reg_predictions(fit);
	vec r = vec_new(fit.y.x->len);
	for (u64 i = 0; i < r.len; i++) {
		r.x[i] = fit.y.x[0].x[i] - p.x[i];
	}
	vec_free(p);
	return r;

}

f64 reg_rmse(reg fit) {
	u64 n = fit.x.x->len;
	u64 p = fit.x.len;
	vec r = reg_residuals(fit);
	f64 rmse = sqrt(vec_var(r) * (n - 1) / (n - p));
	vec_free(r);
	return rmse;
}

vec reg_residuals_norm(reg fit) {
	vec r = reg_residuals(fit);
	f64 rmse = reg_rmse(fit);
	vec n = vec_new(r.len);
	for (u64 i = 0; i < n.len; i++) {
		n.x[i] = r.x[i] / rmse;
	}
	vec_free(r);
	return n;
}

