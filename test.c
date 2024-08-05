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

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[16] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long OScc = 0, PScc = 0;
	int count = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("TV_OS.txt", "w");
	fp4 = fileOpen("TV_PS.txt", "w");
	fp5 = fileOpen("TV_sqr.txt", "w");

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
	}
	printf("OScc = %d\n", OScc / count);
	printf("PScc = %d\n", PScc / count);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
}

void KARA()
{
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;
	FILE* fp5 = NULL;
	FILE* fp6 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[16] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[16] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long KAAddcc = 0, KASubcc = 0;
	unsigned long long KAAdd2cc = 0, KASub2cc = 0;
	int count = 0;

	int depth1 = 0, depth2 = 0;
	int depth3 = 0, depth4 = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("TV_KaraAdd.txt", "w");
	fp4 = fileOpen("TV_KaraSub.txt", "w");
	fp5 = fileOpen("TV_KaraAddD2.txt", "w");
	fp6 = fileOpen("TV_KaraSubD2.txt", "w");

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
		
		depth1 = 0;
		depth2 = 0;
		//카라추바add 연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaAdd(&C, &A, &B, &depth1, 0);
		end = cpucycles();
		KAAddcc += (end - start);
		//printf("KaraAdd depth = %d\n", depth1);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//카라추바sub 연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaSub(&C, &A, &B, &depth2, 0);
		end = cpucycles();
		KASubcc += (end - start);
		//printf("KaraSub depth = %d\n", depth2);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");

		depth3 = 0;
		depth4 = 0;
		//카라추바add2 연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaAddD2(&C, &A, &B, &depth3, 0);
		end = cpucycles();
		KAAdd2cc += (end - start);
		//printf("KaraAdd2 depth = %d\n", depth3);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", C.d[i]);
		}
		fprintf(fp5, "\n\n");

		//카라추바sub2 연산
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaSubD2(&C, &A, &B, &depth4, 0);
		end = cpucycles();
		KASub2cc += (end - start);
		//printf("KaraSub2 depth = %d\n", depth4);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp6, "%08X", C.d[i]);
		}
		fprintf(fp6, "\n\n");
	}
	printf("KAAddcc = %d\n", KAAddcc / count);
	printf("KASubcc = %d\n", KASubcc / count);
	printf("KAAdd2cc = %d\n", KAAdd2cc / count);
	printf("KASub2cc = %d\n", KASub2cc / count);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
}

void GenBigTV()
{
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;
	FILE* fp5 = NULL;
	FILE* fp6 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[1000] = { 0 };
	uint32_t opB[1000] = { 0 };
	uint32_t opC[1000] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	size_t len = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("BigKara512_opA.txt", "w");
	fp4 = fileOpen("BigKara512_opB.txt", "w");
	fp5 = fileOpen("BigKara1024_opA.txt", "w");
	fp6 = fileOpen("BigKara1024_opB.txt", "w");

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		//opA값 저장
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		for (int i = A.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", A.d[i]);
		}
		for (int i = A.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", A.d[i]);
		}
		fprintf(fp3, "\n\n");

		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", B.d[i]);
		}
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", B.d[i]);
		}
		fprintf(fp4, "\n\n");

		for (int i = A.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", A.d[i]);
		}
		for (int i = A.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", A.d[i]);
		}
		for (int i = A.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", A.d[i]);
		}
		fprintf(fp5, "\n\n");

		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp6, "%08X", B.d[i]);
		}
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp6, "%08X", B.d[i]);
		}
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp6, "%08X", B.d[i]);
		}
		fprintf(fp6, "\n\n");
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
}

void BigKARA()
{
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;
	FILE* fp5 = NULL;
	
	FILE* fp6 = NULL;
	FILE* fp7 = NULL;
	FILE* fp8 = NULL;
	FILE* fp9 = NULL;
	FILE* fp10 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[32] = { 0 };
	uint32_t opB[32] = { 0 };
	uint32_t opC[64] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM C = { {0,}, 0, 0 };
	size_t len = 0;
	int depth = 0;
	int count = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long BIG512KAcc = 0, BIG512OScc = 0, BIG512PScc = 0;
	unsigned long long BIG1024KAcc = 0, BIG1024OScc = 0, BIG1024PScc = 0;

	fp1 = fileOpen("BigKara512_opA.txt", "r");
	fp2 = fileOpen("BigKara512_opB.txt", "r");
	fp3 = fileOpen("TV_BigKara512.txt", "w");
	fp4 = fileOpen("TV_BigOS512.txt", "w");
	fp5 = fileOpen("TV_BigPS512.txt", "w");

	fp6 = fileOpen("BigKara1024_opA.txt", "r");
	fp7 = fileOpen("BigKara1024_opB.txt", "r");
	fp8 = fileOpen("TV_BigKara1024.txt", "w");
	fp9 = fileOpen("TV_BigOS1024.txt", "w");
	fp10 = fileOpen("TV_BigPS1024.txt", "w");

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

		//카라추바 연산 512
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaAddD2(&C, &A, &B, &depth, 0);
		end = cpucycles();
		BIG512KAcc += (end - start);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//OS 곱셈연산 512
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		OperandScanning(&C, &A, &B);
		end = cpucycles();
		BIG512OScc += (end - start);

		//OS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");

		//PS 곱셈연산 512
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		ProductScanning(&C, &A, &B);
		end = cpucycles();
		BIG512PScc += (end - start);

		//PS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", C.d[i]);
		}
		fprintf(fp5, "\n\n");

		//opA값 저장
		fscanf(fp6, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB값 저장
		fscanf(fp7, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//카라추바 연산 1024
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		karaAddD2(&C, &A, &B, &depth, 0);
		end = cpucycles();
		BIG1024KAcc += (end - start);

		//카라츄바 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp8, "%08X", C.d[i]);
		}
		fprintf(fp8, "\n\n");

		//OS 곱셈연산 1024
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		OperandScanning(&C, &A, &B);
		end = cpucycles();
		BIG1024OScc += (end - start);

		//OS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp9, "%08X", C.d[i]);
		}
		fprintf(fp9, "\n\n");

		//PS 곱셈연산 1024
		initBignum(opC, A.top + B.top, &C);
		start = cpucycles();
		ProductScanning(&C, &A, &B);
		end = cpucycles();
		BIG1024PScc += (end - start);

		//PS 결과값 파일에 쓰기
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp10, "%08X", C.d[i]);
		}
		fprintf(fp10, "\n\n");
	}
	printf("BIG512KAcc = %d\n", BIG512KAcc / count);
	printf("BIG512OScc = %d\n", BIG512OScc / count);
	printf("BIG512PScc = %d\n", BIG512PScc / count);

	printf("BIG1024KAcc = %d\n", BIG1024KAcc / count);
	printf("BIG1024OScc = %d\n", BIG1024OScc / count);
	printf("BIG1024PScc = %d\n", BIG1024PScc / count);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);

	fclose(fp6);
	fclose(fp7);
	fclose(fp8);
	fclose(fp9);
	fclose(fp10);
}

void REDUCTION()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;

	unsigned char input_str[1000] = { 0 };
	uint32_t P256[8] = { 0 };
	uint32_t opA[16] = { 0 };
	uint32_t opB[8] = { 0 };

	BIGNUM A = { {0,}, 0, 0 };
	BIGNUM B = { {0,}, 0, 0 };
	BIGNUM P = { {0,}, 0, 0 };
	size_t len = 0;

	unsigned long long start = 0, end = 0;
	unsigned long long FASTcc = 0, FAST2cc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_MUL_TV.txt", "r");
	fp2 = fileOpen("TV_FASTREDUCTION.txt", "w");
	fp3 = fileOpen("TV_FASTREDUCTION2.txt", "w");

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

		//빠른 감산2
		initBignum(opB, P.top, &B);
		start = cpucycles();
		fastReduction2(&B, &A, &P);
		end = cpucycles();
		FAST2cc += (end - start);

		//빠른 감산 결과값 파일에 쓰기
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", B.d[i]);
		}
		fprintf(fp3, "\n\n");
	}
	printf("FASTcc = %d\n", FASTcc / count);
	printf("FAST2cc = %d\n", FAST2cc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

void INVERSION()
{
	FILE* fp0 = NULL;
	FILE* fp1 = NULL;
	FILE* fp2 = NULL;
	FILE* fp3 = NULL;
	FILE* fp4 = NULL;

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
	unsigned long long FLTINVcc = 0;
	unsigned long long FLT256INVcc = 0;
	int count = 0;

	fp0 = fileOpen("P256값.txt", "r");
	fp1 = fileOpen("TV_opA_before_INV.txt", "r");
	fp2 = fileOpen("TV_EEA_INVERSION.txt", "w");
	fp3 = fileOpen("TV_FLT_INVERSION.txt", "w");
	fp4 = fileOpen("TV_FLT256_INVERSION.txt", "w");

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

		////Extended Euclidean 역원
		//initBignum(opB, P.top, &B);
		//start = cpucycles();
		//ExtendedEuclidean(&B, &P, &A);
		//end = cpucycles();
		//EEAINVcc += (end - start);

		////역원 결과값 파일에 쓰기
		//for (int i = B.top - 1; i >= 0; i--)
		//{
		//	fprintf(fp2, "%08X", B.d[i]);
		//}
		//fprintf(fp2, "\n\n");

		//FLT 역원
		initBignum(opB, P.top, &B);
		start = cpucycles();
		FLT(&B, &P, &A);
		end = cpucycles();
		FLTINVcc += (end - start);

		//역원 결과값 파일에 쓰기
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", B.d[i]);
		}
		fprintf(fp3, "\n\n");

		//FLT256 역원
		initBignum(opB, P.top, &B);
		start = cpucycles();
		FLT256(&B, &P, &A);
		end = cpucycles();
		FLT256INVcc += (end - start);

		//역원 결과값 파일에 쓰기
		for (int i = B.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", B.d[i]);
		}
		fprintf(fp4, "\n\n");
	}
	//printf("EEAINVcc = %d\n", EEAINVcc / count);
	printf("FLTINVcc = %d\n", FLTINVcc / count);
	printf("FLT256INVcc = %d\n", FLT256INVcc / count);

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}
