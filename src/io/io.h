#pragma once

#include "../../kek.h"

mat read_mat(s64 path);

void write_vec(vec x, s64 path);
void write_mat(mat x, s64 path);

void print_u64(u64 x, s64 name);
void print_f64(f64 x, s64 name);
void print_vec(vec x, s64 name);
void print_mat(mat x, s64 name);
#define print(x) _Generic((x),	\
	u64: print_u64,		\
	f64: print_f64,		\
	vec: print_vec,		\
	mat: print_mat		\
)(x, #x)
