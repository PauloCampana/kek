#include "../kek.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

s64 print_format_string(vec x) {
	u64 max = x.len < 100 ? x.len : 100;
	f64 oom = 0;
	u64 whole = 0;
	for (u64 i = 0; i < max; i++) {
		f64 tmp = log10(fabs(x.x[i]));
		oom += isinf(tmp) ? 0 : tmp / max;
		whole += x.x[i] == round(x.x[i]);
	}
	s64 format = "% 12.2le";
	if (oom > -4 && oom <= -3) format = "% 12.6lf";
	if (oom > -3 && oom <= -2) format = "% 12.5lf";
	if (oom > -2 && oom <= -1) format = "% 12.4lf";
	if (oom > -1 && oom <=  0) format = "% 12.3lf";
	if (oom >  0 && oom <=  1) format = "% 12.2lf";
	if (oom >  1 && oom <=  2) format = "% 12.1lf";
	if (oom >  2 && oom <=  6) format = "% 12.0lf";
	if (whole == max)          format = "% 12.0lf";
	if (oom < -4 || oom >=  6) format = "% 12.2le";
	return format;
}

void print_vec_(vec x, s64 name) {
	u64 max = x.len < 100 ? x.len : 100;
	s64 format = print_format_string(x);
	printf("%s [%llu]\n", name, x.len);
	for (u64 i = 0; i < max; i++) {
		printf(format, x.x[i]);
		if (i % 10 == 9) printf("\n");
	}
	if (x.len % 10 != 0) printf("\n");
}

void print_mat_(mat x, s64 name) {
	u64 rowmax = x.x[0].len < 10 ? x.x[0].len : 10;
	u64 colmax = x.len < 10 ? x.len : 10;
	printf("%s [%llu x %llu]\n", name, x.x[0].len, x.len);
	s64 *formats = malloc(x.len * sizeof formats[0]);
	printf("          ");
	for (u64 j = 0; j < colmax; j++) {
		if (x.colnames != NULL) printf("%12.11s", x.colnames[j]);
		formats[j] = print_format_string(x.x[j]);
	}
	printf("\n");
	for (u64 i = 0; i < rowmax; i++) {
		if (x.rownames != NULL) printf("%-10.9s", x.rownames[i]);
		for (u64 j = 0; j < colmax; j++) {
			printf(formats[j], x.x[j].x[i]);
		}
		printf("\n");
	}
	free(formats);
}
