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
void KARA();
void GenBigTV();
void BigKARA();
void REDUCTION();
void INVERSION();