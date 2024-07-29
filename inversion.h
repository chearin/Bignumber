#pragma once
#include "bn.h"
#include "reduction.h"
#include "karatsuba.h"

void BignumberCopy(BIGNUM* d, const BIGNUM* r);
void BignumberLShift32(BIGNUM* r, const BIGNUM* a, const uint32_t n);
void BignumberLShift(BIGNUM* r, const BIGNUM* a, const uint32_t n);
void BignumberDivision(BIGNUM* q, BIGNUM* r, const BIGNUM* a, const BIGNUM* b);

void ExtendedEuclidean(BIGNUM* inv, const BIGNUM* P, const BIGNUM* a);
void FLT(BIGNUM* inv, const BIGNUM* P, const BIGNUM* a);
void FLT256(BIGNUM* inv, const BIGNUM* P, const BIGNUM* a);