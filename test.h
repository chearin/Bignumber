#pragma once
#include <stdio.h>
#include <stdint.h>
#include "util.h"
#include "bn.h"
#include "karatsuba.h"
#include "reduction.h"
#include "inversion.h"

void ADDSUB();
void MUL();
void REDUCTION();
void INVERSION();