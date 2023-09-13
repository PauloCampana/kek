#include "../kek.h"

f64 sum(vec x) {
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		switch (x.type) {
		case SIGNED:
			sum += i64(x)[i];
			break;
		case UNSIGNED:
			sum += u64(x)[i];
			break;
		case FLOAT:
			sum += f64(x)[i];
			break;
		}
	}
	return sum;
}

f64 mean(vec x) {
	return sum(x) / x.len;
}

f64 sumprod(vec x1, vec x2) {
	f64 sum = 0;
	for (u64 i = 0; i < x1.len; i++) {
		switch (x1.type) {
		case SIGNED:
			sum += i64(x1)[i] * i64(x2)[i];
			break;
		case UNSIGNED:
			sum += u64(x1)[i] * u64(x2)[i];
			break;
		case FLOAT:
			sum += f64(x1)[i] * f64(x2)[i];
			break;
		}
	}
	return sum;
}

f64 var(vec x) {
	f64 xbar = mean(x);
	f64 sumsq = sumprod(x, x);
	return (sumsq - x.len * xbar * xbar) / (x.len - 1);
}

f64 sd(vec x) {
	return sqrt(var(x));
}

f64 cov(vec x1, vec x2) {
	f64 xbar1 = mean(x1);
	f64 xbar2 = mean(x2);
	f64 sumsq = sumprod(x1, x2);
	return (sumsq - x1.len * xbar1 * xbar2) / (x1.len - 1);
}

f64 cor(vec x1, vec x2) {
	return cov(x1, x2) / sd(x1) / sd(x2);
}
