#pragma once
#include <stdio.h>
#include <stdint.h>
#include "bn.h"

void OperandScanning(const uint32_t* opA, const uint32_t* opB, uint32_t* opC);
void ProductScanning(const uint32_t* opA, const uint32_t* opB, uint32_t* opC);
