#include "../kek.h"
#include <math.h>
#include <stdio.h>

void print_vec(vec x) {
	u64 max = x.len < 100 ? x.len : 100;
	f64 oom = 0;
	f64 whole = 0;
	for (u64 i = 0; i < max; i++) {
		oom += log10(fabs(x.x[i]));
		whole += x.x[i] == ceil(x.x[i]);
	}
	oom /= max;
	s64 format;
	if      (isinf(oom))   format = "% 12.0lf";
	else if (whole == max) format = "% 12.0lf";
	else if (oom < -4) format = "% 12.2le";
	else if (oom < -3) format = "% 12.6lf";
	else if (oom < -2) format = "% 12.5lf";
	else if (oom < -1) format = "% 12.4lf";
	else if (oom <  0) format = "% 12.3lf";
	else if (oom <  1) format = "% 12.2lf";
	else if (oom <  2) format = "% 12.1lf";
	else if (oom <  6) format = "% 11.0lf.";
	else               format = "% 12.2le";
	printf("vector [%llu]\n", x.len);
	for (u64 i = 0; i < max; i++) {
		printf(format, x.x[i]);
		if (i % 10 == 9) printf("\n");
	}
	if (x.len % 10 != 0) printf("\n");
}

void print_df(df data) {
	u64 max = data.nrow < 10 ? data.nrow : 10;
	printf("dataframe [%llu x %llu]\n", data.nrow, data.ncol);
	for (u64 j = 0; j < data.ncol; j++) {
		printf("%15.14s", data.colnames[j]);
	}
	printf("\n");
	for (u64 j = 0; j < data.ncol; j++) {
		printf("        <float>");
	}
	printf("\n");
	for (u64 i = 0; i < max; i++) {
		for(u64 j = 0; j < data.ncol; j++) {
			printf("%15.3lf", data.var[j].x[i]);
		}
		printf("\n");
	}
	data.nrow < 10 ? printf(" ") : printf("%llu more rows\n", data.nrow - 10);
}
