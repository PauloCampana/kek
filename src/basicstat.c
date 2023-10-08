#include "../kek.h"
#include <math.h>

f64 sum(vec x) {
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		sum += x.x[i];
	}
	return sum;
}

f64 mean(vec x) {
	return sum(x) / x.len;
}

f64 var(vec x) {
	f64 xbar = mean(x);
	f64 sum = 0;
	for (u64 i = 0; i < x.len; i++) {
		sum += x.x[i] * x.x[i];
	}
	return (sum - x.len * xbar * xbar) / (x.len - 1);
}

f64 sd(vec x) {
	return sqrt(var(x));
}

f64 cov(vec x1, vec x2) {
	f64 xbar1 = mean(x1);
	f64 xbar2 = mean(x2);
	f64 sum = 0;
	for (u64 i = 0; i < x1.len; i++) {
		sum += x1.x[i] * x2.x[i];
	}
	return (sum - x1.len * xbar1 * xbar2) / (x1.len - 1);
}

f64 cor(vec x1, vec x2) {
	f64 xbar1 = mean(x1);
	f64 xbar2 = mean(x2);
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
