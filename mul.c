#define _CRT_SECURE_NO_WARNINGS
#include "mul.h"

void OperandScanning(const BIGNUM* A, const BIGNUM* B, BIGNUM* C)
{
	//uint64_t UV = 0;
	//uint32_t U = 0;
	//uint32_t V = 0;

	//for (int i = 0; i < 16; i++)
	//{
	//	C[i] = 0;
	//}

	//for (int i = 0; i < 8; i++)
	//{
	//	U = 0;
	//	for (int j = 0; j < 8; j++)
	//	{
	//		UV = C[i + j] + (uint64_t)A[i] * B[j] + U;
	//		U = UV >> 32;
	//		V = (uint32_t)UV;
	//		C[i + j] = V;
	//	}
	//	C[i + 8] = U;
	//}
}

void ProductScanning(const BIGNUM* A, const BIGNUM* B, BIGNUM* C)
{
	//uint64_t UV = 0;
	//uint64_t tmp = 0;
	//uint32_t U = 0;
	//uint32_t V = 0;
	//uint32_t R[3] = { 0 };
	//uint32_t carry = 0;

	//for (int i = 0; i < 16; i++)
	//{
	//	opC[i] = 0;
	//}

	//for (int k = 0; k < 15; k++)
	//{
	//	for (int i = 0; i < 8; i++)
	//	{
	//		for (int j = 0; j < 8; j++)
	//		{
	//			if (i + j == k)
	//			{
	//				UV = (uint64_t)opA[i] * opB[j];
	//				U = UV >> 32;
	//				V = (uint32_t)UV;

	//				tmp = (uint64_t)R[0] + V;
	//				carry = tmp >> 32;
	//				R[0] = (uint32_t)tmp;

	//				tmp = (uint64_t)R[1] + U + carry;
	//				carry = tmp >> 32;
	//				R[1] = (uint32_t)tmp;

	//				R[2] += carry;
	//			}
	//		}
	//	}
	//	opC[k] = R[0];
	//	R[0] = R[1];
	//	R[1] = R[2];
	//	R[2] = 0;
	//}
	//opC[15] = R[0];
}

void Squaring()
{

}