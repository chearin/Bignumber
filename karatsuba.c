#include "karatsuba.h"

void kara(BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	BIGNUM R0 = { {0,}, 0, 0 };
	BIGNUM R1 = { {0,}, 0, 0 };
	BIGNUM R2 = { {0,}, 0, 0 };

	BIGNUM a0 = { {0,}, 0, 0 };
	BIGNUM a1 = { {0,}, 0, 0 };
	BIGNUM asum = { {0,}, 0, 0 };

	BIGNUM b0 = { {0,}, 0, 0 };
	BIGNUM b1 = { {0,}, 0, 0 };
	BIGNUM bsum = { {0,}, 0, 0 };

	uint32_t AB[2] = { 0, };

	if (a->top != b->top)
	{
		printf("karatsuba len error\n");
		return;
	}

	//base case
	if (a->top == 1)
	{
		divisionMul(AB, a->d[0], b->d[0]);
		r->d[0] = AB[0];
		r->d[1] = AB[1];
		r->top = 2;
		return;
	}
	
	//recursive case
	//a0, a1, b0, b1 ³ª´©±â
	for (int i = 0; i < a->top / 2; i++)
	{
		a0.d[i] = a->d[i];
		a0.top++;
		b0.d[i] = b->d[i];
		b0.top++;
	}
	for (int i = (a->top + 1) / 2; i < a->top; i++)
	{	
		a1.d[i - a->top / 2] = a->d[i];
		a1.top++;
		b1.d[i - a->top / 2] = b->d[i];
		b1.top++;
	}
	//asum = a1 + a0, bsum = b1 + b0
	BignumberAdd(&asum, &a0, &a1);
	if (asum.cb)
	{
		asum.d[asum.top] = 1;
		asum.top++;
	}
	BignumberAdd(&bsum, &b0, &b1);
	if (bsum.cb)
	{
		bsum.d[bsum.top] = 1;
		bsum.top++;
	}

	//R2 = a1 * b1
	kara(&R2, &a1, &b1);
	//R0 = a0 * b0
	kara(&R0, &a0, &b0);
	//R1 = asum * bsum - R2 - R0
	kara(&R1, &asum, &bsum);
	BignumberSub(&R1, &R1, &R2);
	BignumberSub(&R1, &R1, &R0);

	//R2*2^2l
	for (int i = R2.top - 1; i >= 0; i--)
	{
		R2.d[i + a0.top * 2] = R2.d[i];
		R2.d[i] = 0;
	}
	R2.top += (a0.top * 2);

	//R1*2^l
	for (int i = R1.top - 1; i >= 0; i--)
	{
		R1.d[i + a0.top] = R1.d[i];
		R1.d[i] = 0;
	}
	R1.top += a0.top;

	//R2*2^2l + R1*2^l + R0
	BignumberAdd(r, &R2, &R1);
	if (r->cb)
	{
		r->d[r->top] = 1;
		r->top++;
	}
	BignumberAdd(r, r, &R0);
	if (r->cb)
	{
		r->d[r->top] = 1;
		r->top++;
	}
}