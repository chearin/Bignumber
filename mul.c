#define _CRT_SECURE_NO_WARNINGS
#include "mul.h"

//���� ����
void divisionMul(uint32_t* c, const uint32_t a, const uint32_t b)
{
	uint32_t carry = 0;
	uint32_t sum = 0;
	uint32_t r = 0;
	uint32_t t1 = 0, t2 = 0, t3 = 0;

	t1 = (a & MASK) * (b & MASK);
	r = (t1 & MASK);
	t2 = (a >> 16) * (b & MASK);
	t3 = (a & MASK) * (b >> 16);
	sum = (t1 >> 16) + (t2 & MASK) + (t3 & MASK);
	carry = (sum >> 16);
	r += (sum << 16);
	c[0] = r;

	t1 = (a >> 16) * (b >> 16);
	sum = (t2 >> 16) + (t3 >> 16) + (t1 & MASK) + carry;
	carry = (sum >> 16);
	r = (sum & MASK);
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
			//ĳ�� Ȯ��
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

	for (int i = 0; i < r->top; i++)
	{
		r->d[i] = 0;
	}

	for (int k = 0; k < r->top - 1; k++)
	{
		for (int i = 0; i < a->top; i++)
		{
			int j = k - i;
			if (j < 0)
			{
				break;
			}
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
		r->d[k] = R[0];
		R[0] = R[1];
		R[1] = R[2];
		R[2] = 0;
	}
	if (r->top != 16)
	{
		printf("error!!");
	}
	r->d[r->top - 1] = R[0];
}

void Squaring(BIGNUM* r, const BIGNUM* a)
{
	uint32_t UV[2] = { 0, };
	uint32_t R[3] = { 0, };
	uint32_t sum = 0;
	uint32_t carry = 0;

	for (int k = 0; k < a->top * 2 - 1; k++)
	{
		for (int i = 0; i <= k / 2; i++)
		{
			int j = k - i;
			divisionMul(UV, a->d[i], a->d[j]);
			if (i != j)
			{
				// UV 2�� ���ֱ�
				carry = UV[1] >> 31;
				UV[0] <<= 1;
				UV[1] <<= 1;
				R[2] += carry;
			}
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
		r->d[k] = R[0];
		R[0] = R[1];
		R[1] = R[2];
		R[2] = 0;
	}
	r->d[r->top - 1] = R[0];
}