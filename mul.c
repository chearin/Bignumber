#define _CRT_SECURE_NO_WARNINGS
#include "mul.h"

//ºÐÇÒ °ö¼À
void divisionMul(uint32_t* c, const uint32_t a, const uint32_t b)
{
	uint32_t carry = 0;
	uint32_t sum = 0;
	uint32_t r = 0;
	uint32_t t1 = 0, t2 = 0, t3 = 0;

	t1 = (a & 0x0000ffff) * (b & 0x0000ffff);
	r = (t1 & 0x0000ffff);
	t2 = (a >> 16) * (b & 0x0000ffff);
	t3 = (a & 0x0000ffff) * (b >> 16);
	sum = (t1 >> 16) + (t2 & 0x0000ffff) + (t3 & 0x0000ffff);
	carry = (sum >> 16);
	r += (sum << 16);
	c[0] = r;

	t1 = (a >> 16) * (b >> 16);
	sum = (t2 >> 16) + (t3 >> 16) + (t1 & 0x0000ffff) + carry;
	carry = (sum >> 16);
	r = (sum & 0x0000ffff);
	sum = (t1 >> 16) + carry;
	r += (sum << 16);
	c[1] = r;
}

void OperandScanning(BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	uint32_t AB[2] = { 0, };
	uint32_t UV[2] = { 0, };
	uint32_t sum = 0;
	uint32_t carry = 0;
	uint32_t tmp = 0;

	for (int i = 0; i < r->top; i++)
	{
		r->d[i] = 0;
	}

	for (int i = 0; i < a->top; i++)
	{
		UV[1] = 0;
		for (int j = 0; j < b->top; j++)
		{
			divisionMul(AB, a->d[i], b->d[j]);
			//Ä³¸® È®ÀÎ
			carry = 0;
			sum = r->d[i + j] + AB[0];
			if (sum < r->d[i + j])
			{
				carry = 1;
				
			}
			sum += UV[1];
			if (sum < UV[1])
			{
				carry += 1;
			}

			UV[0] = sum;
			UV[1] = AB[1] + carry;
			r->d[i + j] = UV[0];
		}
		r->d[i + b->top] = UV[1];
	}
}

void ProductScanning(BIGNUM* r, const BIGNUM* a, const BIGNUM* b)
{
	uint32_t UV[2] = { 0, };
	uint32_t R[3] = { 0, };
	uint32_t sum = 0;
	uint32_t carry = 0;
	uint32_t tmp = 0;

	for (int i = 0; i < r->top; i++)
	{
		r->d[i] = 0;
	}

	for (int k = 0; k < r->top - 1; k++)
	{
		for (int i = 0; i < a->top; i++)
		{
			for (int j = 0; j < b->top; j++)
			{
				if (i + j == k)
				{
					divisionMul(UV, a->d[i], b->d[j]);
					carry = 0;
					sum = R[0] + UV[0];
					if (sum < R[0])
					{
						carry = 1;
					}
					R[0] = sum;
					
					sum = R[1] + carry;
					carry = 0;
					if (sum < R[1])
					{
						carry = 1;
					}
					sum += UV[1];
					if (sum < UV[1])
					{
						carry += 1;
					}
					R[1] = sum;

					R[2] += carry;
				}
			}
		}
		r->d[k] = R[0];
		R[0] = R[1];
		R[1] = R[2];
		R[2] = 0;
	}
	r->d[r->top-1] = R[0];
}

void Squaring()
{

}