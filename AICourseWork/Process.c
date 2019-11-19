#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* process block
* author: Sun Ray 2019.11.19
*/
Qpointer initialize() {	// ��Ŀ��ʼ��

	const int standard[3][3] = { {1, 2, 3}, {8, 0, 4}, {7, 6, 5} };
	const long unique = converseMatrix(standard);
	const int inversion = countInverseNumber(assistInverse(standard));

	Qpointer open = createQueue(40, unique, inversion);

	for (int i = 0; i < 3; i++) {	// ��ʼ���Ź���

		for (int j = 0; j < 3; j++) {

			open->standard[i][j] = standard[i][j];

		}

	}

	return open;

}


Ipointer input(Qpointer open) {	// input����

	Ipointer nine = (Ipointer)malloc(ISIZE);

	FILE* fp;

	char fileName[256];

	printf("�������ļ���(���ּ�ո�ָ�)��");

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


void helper(Hpointer helper, char name[]) {	// ����handle����

	printf("\n---------- %s ����·�� ----------\n", name);

	if (helper->flag == True) {

		printf("\nsearch successful! \n");

		int times = backtrack(helper->end);

		printf("\n�����ƶ� %d ������Ŀ��״̬. \n\n", times);

	}
	else if (helper->flag == False) {

		printf("\nsearch failed! \n");
		printf("\nĿ��״̬���ɴ�! \n");

	}
	else {	// isOk = Unknown

		printf("\nsearch successful! \n");
		printf("�׽�㼴ΪĿ��ڵ�, �����ƶ�(�ƶ� 0 ������Ŀ��״̬). \n");

	}

}


void processBlock(Qpointer open, Ipointer begin) {	// ��װ

	char* names[] = { "������������㷨", "ȫ�����������㷨", "A*�㷨" };

	for (int i = 0; i < 3; i++) {

		Cpointer closed = getClosed(begin);	// ��ʼ��, ���closed��;

		run(open, begin, i, names[i], closed);

		destoryQ(open);	// ��ն���

		helper(store[i], names[i]);

		dostoryClosed(closed);	// �������

	}

}
