#include "kek.h"
#include <stdio.h>
#include <string.h>

int main(void) {
	mat diamonds = read_mat("data/diamonds.csv");
	print_mat(diamonds);
}
