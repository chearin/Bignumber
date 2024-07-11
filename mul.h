#pragma once
#include <stdio.h>
#include <stdint.h>
#include "bn.h"

void divisionMul(uint32_t* r, const uint32_t a, const uint32_t b);

void OperandScanning(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
void ProductScanning(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
