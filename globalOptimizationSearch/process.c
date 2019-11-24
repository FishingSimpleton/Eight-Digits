#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


MinHpointer initialize() {	// ��Ŀ��ʼ��

	//const int standard[3][3] = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };
	const int standard[3][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8} };	// 31step: matching max.txt:
	const long unique = converseMatrix(standard);
	const int inversion = countInverseNumber(assistInverse(standard));

	MinHpointer open = createMinHeap(MAXCAPACITY, unique, inversion);

	for (int i = 0; i < 3; i++) {	// ��ʼ���Ź���

		for (int j = 0; j < 3; j++) {

			open->standard[i][j] = standard[i][j];

		}

	}

	return open;

}


Ipointer input(MinHpointer open) {	// input����

	Ipointer nine = (Ipointer)malloc(ISIZE);

	FILE* fp;

	char fileName[256];

	printf("�������ļ���(�ı�Ϊ��������)��");

	scanf("%s", &fileName);

	char value = NULL;

	int sequence[9] = { 0 };

	int k = 0;

	fp = fopen(fileName, "r");  /* ��ֻ����ʽ��ȡ�ļ� */

	while ((value = fgetc(fp)) != EOF) {    /* ���ļ�δ��ĩβʱ��ͳ�Ƹ���Ӧ�ַ���Ȩֵ (��Ƶ��) */

		if (value != ' ') {

			int ok = value - '0';

			sequence[k++] = ok;

		}

	}

	k = 0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			nine->digit[i][j] = sequence[k++];

		}

	}

	nine->unique = converseMatrix(nine->digit);

	locateZeros(nine);	// ��λ�׽ڵ� "0" ������

	nine->blockDirection = NONE;
	nine->parent = NULL;

	getWeight(open, nine);

	return nine;

}