#define _CRT_SECURE_NO_WARNINGS
#include "test.h"
#include "cpucycles.h"

void ADDSUB()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t P256[8] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[8] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	BIGNUM P = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long ADDcc = 0, SUBcc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_opA_add.txt", "r");
	fp2 = fileOpen("TV_opB_add.txt", "r");
	fp3 = fileOpen("TV_PF_add.txt", "w");
	fp4 = fileOpen("TV_PF_sub.txt", "w");

	//p256값 저장
	fscanf(fp0, "%s", input_str);
	len = strlen(input_str) / (sizeof(int) * 2);
	str2hex(input_str, P256, len);
	initBignum(P256, len, &P);

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//소수체 덧셈연산
		initBignum(opC, len, &C);
		start = cpucycles();
		PF_addition(&C, &P, &A, &B);
		end = cpucycles();
		ADDcc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//소수체 뺄셈연산
		initBignum(opC, len, &C);
		start = cpucycles();
		PF_substraction(&C, &P, &A, &B);
		end = cpucycles();
		SUBcc += (end - start);

		//결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");
	}
	printf("ADDcc = %d\n", ADDcc / count);
	printf("SUBcc = %d\n", SUBcc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}

void MUL()
{
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;
	FILE* fp5 = NULL;
	FILE* fp6 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[16] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long OScc = 0, PScc = 0, KAcc = 0;
	int count = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("TV_OS.txt", "w");
	fp4 = fileOpen("TV_PS.txt", "w");
	fp5 = fileOpen("TV_sqr.txt", "w");
	fp6 = fileOpen("TV_kara.txt", "w");

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//OS 곱셈연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		OperandScanning(&C, &A, &B);
		end = cpucycles();
		OScc += (end - start);

		//OS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//PS 곱셈연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		ProductScanning(&C, &A, &B);
		end = cpucycles();
		PScc += (end - start);

		//PS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");

		//제곱연산
		initBignum(opC, A.top + B.top, &C);
		Squaring(&C, &A);

		//제곱 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", C.d[i]);
		}
		fprintf(fp5, "\n\n");
	
		//카라추바 연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		kara(&C, &A, &B);
		end = cpucycles();
		KAcc += (end - start);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp6, "%08X", C.d[i]);
		}
		fprintf(fp6, "\n\n");
		
	}
	printf("OScc = %d\n", OScc / count);
	printf("PScc = %d\n", PScc / count);
	printf("KAcc = %d\n", KAcc / count);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
}

void REDUCTION()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t P256[8] = { 0 };
	uint32_t opA[16] = { 0 };
	uint32_t opB[8] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM P = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long FASTcc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_MUL_TV.txt", "r");
	fp2 = fileOpen("TV_FASTREDUCTION.txt", "w");

	//p256값 저장
	fscanf(fp0, "%s", input_str);
	len = strlen(input_str) / (sizeof(int) * 2);
	str2hex(input_str, P256, len);
	initBignum(P256, len, &P);

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//빠른 감산
		initBignum(opB, P.top, &B);
		start = cpucycles();
		fastReduction(&B, &A, &P);
		end = cpucycles();
		FASTcc += (end - start);

		//빠른 감산 결과값 파일에 쓰기
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp2, "%08X", B.d[i]);
		}
		fprintf(fp2, "\n\n");
	}
	printf("FASTcc = %d\n", FASTcc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
}

void INVERSION()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t P256[8] = { 0 };
	uint32_t opA[16] = { 0 };
	uint32_t opB[8] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM P = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long EEAINVcc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_opA_before_INV.txt", "r");
	fp2 = fileOpen("TV_EEA_INVERSION.txt", "w");

	//p256값 저장
	fscanf(fp0, "%s", input_str);
	len = strlen(input_str) / (sizeof(int) * 2);
	str2hex(input_str, P256, len);
	initBignum(P256, len, &P);

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//Extended Euclidean 역원
		initBignum(opB, P.top, &B);
		start = cpucycles();
		ExtendedEuclidean(&B, &A, &P);
		end = cpucycles();
		EEAINVcc += (end - start);

		//역원 결과값 파일에 쓰기
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp2, "%08X", B.d[i]);
		}
		fprintf(fp2, "\n\n");
	}
	printf("EEAINVcc = %d\n", EEAINVcc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
}
