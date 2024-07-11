#pragma once
#include <stdio.h>
#include <stdint.h>

typedef struct bignum_st {
    uint32_t d[16]; //����, �������� d[8]�� carry �Ǵ� borrow�� ������ 1
    int top; //���� ������� d �迭�� ũ��
}BIGNUM;

void initBignum(const uint32_t* num, const size_t inlen, BIGNUM* BN);
uint32_t compare(const BIGNUM* a, const BIGNUM* b);

void BignumberAdd(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);
void BignumberSub(BIGNUM* r, const BIGNUM* a, const BIGNUM* b);

void PF_addition(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b);
void PF_substraction(BIGNUM* c, const BIGNUM* P, const BIGNUM* a, const BIGNUM* b);