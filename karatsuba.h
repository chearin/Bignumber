#pragma once
#include "bn.h"
#include "mul.h"

void karaAdd(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, int* depth, int x);
void karaSub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, int* depth, int x);

void karaAddD2(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, int* depth, int x);
void karaSubD2(BIGNUM* r, const BIGNUM* a, const BIGNUM* b, int* depth, int x);