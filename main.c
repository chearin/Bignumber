#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "util.h"
#include "bn.h"
#include "mul.h"
#include "test.h"
#include "cpucycles.h"
#include "karatsuba.h"
#include "reduction.h"
#include "inversion.h"

int main()
{
	//ADDSUB();
	//MUL();
	KARA();
	//GenBigTV();
	//BigKARA();
	//REDUCTION();
	//INVERSION();

	return 0;
}