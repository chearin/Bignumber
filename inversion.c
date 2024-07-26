#include "inversion.h"

void BignumberCopy(BIGNUM* d, const BIGNUM* r)
{
	for (int i = 0; i < r->top; i++)
	{
		d->d[i] = r->d[i];
	}
	d->top = r->top;
}

void BignumShift(BIGNUM* r, const BIGNUM* a, uint32_t n)
{
	
}

void BinaryLongDivision(uint32_t* q, uint32_t* r, const uint32_t a, const uint32_t b)
{
	// R < b, b는 32비트 이내, R << 1에서 초과 비트 없음
	uint32_t R = 0;

	for (int i = 7; i >= 0; i++)
	{
		R = R << 1 + ((a >> i) & 0b00000001);
		if (R > b)
		{

		}
	}
}

void BignumberDivision(BIGNUM* q, BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	//BIGNUM R = { 0, };
	////몫과 나머지 초기화
	//for (int i = 0; i < q->top; i++)
	//{
	//	q->d[i] = 0;
	//}
	//q->top = 0;
	//for (int i = 0; i < r->top; i++)
	//{
	//	r->d[i] = 0;
	//}
	//r->top = 0;

	

}

void ExtendedEuclidean(BIGNUM* inv, const BIGNUM* P, const BIGNUM* a)
{
	BIGNUM u = { 0, };
	BIGNUM v = { 0, };
	BIGNUM x = { 0, };
	BIGNUM x1 = { 0, };
	BIGNUM x2 = { 0, };
	BIGNUM q = { 0, };
	BIGNUM r = { 0, };

	BIGNUM one = { 0, };
	one.d[0] = 1;
	one.top = 1;

	x1.d[0] = 1;
	x1.top = 1;

	x2.d[0] = 0;
	x1.top = 1;

	while (compare(&one, &u) != 0)
	{
		BignumberDivision(&q, &r, &v, &u);
		kara(&x1, &q, &x1);
		BignumberSub(&x, &x2, &x1);

		BignumberCopy(&v, &u);
		BignumberCopy(&u, &r);
		BignumberCopy(&x2, &x1);
		BignumberCopy(&x1, &x);
	}
	fastReduction(&inv, &x1, P);
}

void FLT(BIGNUM* inv, const BIGNUM* P, const BIGNUM* a)
{

}