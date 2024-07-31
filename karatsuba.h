#pragma once
#include "bn.h"
#include "mul.h"

void karaAdd(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
void karaSub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);