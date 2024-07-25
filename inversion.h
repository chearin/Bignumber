#pragma once
#include "bn.h"
#include "reduction.h"
#include "karatsuba.h"

void BignumberCopy(BIGNUM* d, const BIGNUM* r);
void BignumberDivision(BIGNUM* q, BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
void ExtendedEuclidean(BIGNUM* ai, const BIGNUM* P, const BIGNUM* a);