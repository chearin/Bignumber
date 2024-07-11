#define _CRT_SECURE_NO_WARNINGS
#include "test.h"

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

	BIGNUM A = { {0,}, 0};
	BIGNUM B = { {0,}, 0 };
	BIGNUM C = { {0,}, 0 };
	BIGNUM P = { {0,}, 0 };
	size_t len = 0;

	fp0 = fileOpen("P256��.txt", "r");
	fp1 = fileOpen("TV_opA_add.txt", "r");
	fp2 = fileOpen("TV_opB_add.txt", "r");
	fp3 = fileOpen("TV_PF_add.txt", "w");
	fp4 = fileOpen("TV_PF_sub.txt", "w");

	//p256�� ����
	fscanf(fp0, "%s", input_str);
	len = strlen(input_str) / (sizeof(int) * 2);
	str2hex(input_str, P256, len);
	initBignum(P256, len, &P);
	int count = 0;
	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		count++;
		//opA�� ����
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB�� ����
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//�Ҽ�ü ��������
		initBignum(opC, len, &C);
		PF_addition(&C, &P, &A, &B);

		//����� ���Ͽ� ����
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//�Ҽ�ü ��������
		initBignum(opC, len, &C);
		PF_substraction(&C, &P, &A, &B);

		//����� ���Ͽ� ����
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");
	}

	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}

void MUL()
{
	FILE* fp1;
	FILE* fp2;
	FILE* fp3;
	FILE* fp4;
	FILE* fp5;

	unsigned char input_str[1000] = { 0 };
	uint32_t opA[8] = { 0 };
	uint32_t opB[8] = { 0 };
	uint32_t opC[16] = { 0 };

	BIGNUM A = { {0,}, 0 };
	BIGNUM B = { {0,}, 0 };
	BIGNUM C = { {0,}, 0 };
	size_t len = 0;

	fp1 = fileOpen("TV_opA.txt", "r");
	fp2 = fileOpen("TV_opB.txt", "r");
	fp3 = fileOpen("TV_PF_OS.txt", "w");
	fp4 = fileOpen("TV_PF_PS.txt", "w");
	fp5 = fileOpen("TV_PF_sqr.txt", "w");

	while (fscanf(fp1, "%s", input_str) != EOF)
	{
		//opA�� ����
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opA, len);
		initBignum(opA, len, &A);

		//opB�� ����
		fscanf(fp2, "%s", input_str);
		len = strlen(input_str) / (sizeof(int) * 2);
		str2hex(input_str, opB, len);
		initBignum(opB, len, &B);

		//OS ��������
		initBignum(opC, A.top + B.top, &C);
		OperandScanning(&C, &A, &B);

		//����� ���Ͽ� ����
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp3, "%08X", C.d[i]);
		}
		fprintf(fp3, "\n\n");

		//PS ��������
		initBignum(opC, A.top + B.top, &C);
		ProductScanning(&C, &A, &B);

		//����� ���Ͽ� ����
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp4, "%08X", C.d[i]);
		}
		fprintf(fp4, "\n\n");

		//��������
		initBignum(opC, A.top + B.top, &C);
		Squaring(&C, &A, &B);

		//����� ���Ͽ� ����
		for (int i = C.top - 1; i >= 0; i--)
		{
			fprintf(fp5, "%08X", C.d[i]);
		}
		fprintf(fp5, "\n\n");
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
}