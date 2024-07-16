#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "util.h"
#include "bn.h"
#include "mul.h"
#include "test.h"
#include "cpucycles.h"
#include "karatsuba.h"

int main()
{
	ADDSUB();
	MUL();

	return 0;
}