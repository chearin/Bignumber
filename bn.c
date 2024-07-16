#define _CRT_SECURE_NO_WARNINGS
#include "bn.h"

void initBignum(const uint32_t* num, const size_t inlen, BIGNUM* BN)
{
	for (int i = 0; i < inlen; i++)
	{
		BN->d[i] = num[i];
	}
	for (int i = inlen; i < 16; i++)
	{
		BN->d[i] = 0;
	}
	BN->top = inlen;
}

//a > b 이면 1, a == b 이면 0, a < b 이면 -1 반환
uint32_t compare(const BIGNUM* a, const BIGNUM* b)
{
	if (a->top == b->top)
	{
		for (int i = 0; i < a->top; i++)
		{
			if (a->d[a->top - 1 - i] > b->d[a->top - 1 - i])
			{
				return 1;
			}
			else if (a->d[a->top - 1 - i] < b->d[a->top - 1 - i])
			{
				return -1;
			}
		}
		return 0;
	}
	else
	{
		return -1 + 2 * (a->top > b->top);
	}
}

void BignumberAdd(BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	uint32_t carry = 0;
	uint32_t sum = 0;

	//a, b를 긴 길이인 것과 짧은 길이인 것으로 구분
	BIGNUM* l = a;
	BIGNUM* s = b;

	if (l->top < s->top)
	{
		l = b;
		s = a;
	}

	for (int i = 0; i < s->top; i++)
	{
		sum = l->d[i] + s->d[i];
		if (sum < l->d[i])
		{
			sum += carry;
			carry = 1;
		}
		else
		{
			sum += carry;
			if (sum < carry)
			{
				carry = 1;
			}
			else
			{
				carry = 0;
			}
		}
		r->d[i] = sum;
	}
	for (int i = s->top; i < l->top; i++)
	{
		sum = l->d[i] + carry;
		carry = (sum < l->d[i]);
		r->d[i] = sum;
	}

	r->d[8] = carry;
	r->top = l->top;
}

void BignumberSub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	uint32_t borrow = 0;
	size_t len = a->top;

	// len은 a, b 중 긴쪽
	if (a->top < b->top)
	{
		len = b->top;
	}

	for (int i = 0; i < len; i++)
	{
		r->d[i] = (a->d[i] - b->d[i] - borrow);

		// a->d[i] == b->d[i] 일때는 borrow 유지
		if (a->d[i] < b->d[i])
		{
			borrow = 1;
		}
		else if(a->d[i] > b->d[i])
		{
			borrow = 0;
		}
	}
	r->d[8] = borrow;
	r->top = len;

	// 결과의 앞자리부터 0인지를 확인하고 길이를 줄이는 함수
	for (int i = r->top - 1; i >= 0; i--)
	{
		if (r->d[i] == 0)
		{
			r->top--;
		}
		else
		{
			break;
		}
	}
}

void PF_addition(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b)
{
	uint32_t cmp = 0;

	BignumberAdd(c, a, b);
	cmp = compare(c, P);
	if (c->d[8] || cmp == 0 || cmp == 1)
	{
		BignumberSub(c, c, P);
	}
}

void PF_substraction(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b)
{
	BignumberSub(c, a, b);
	if (c->d[8])
	{
		BignumberAdd(c, c, P);
	}
}