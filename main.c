#include "kek.h"
#include <stdio.h>

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv", 53940, 7);
	print_mat(diamonds);
}
