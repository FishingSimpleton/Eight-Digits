#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

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


Ipointer input() {	// input����

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

	locateZeros(nine);	// ��λ�׽ڵ� "0" ������

	nine->blockDirection = NONE;
	nine->parent = NULL;

	return nine;

}


void handle(Qpointer open, Ipointer begin) {	// ������

	Ipointer node = begin;

	if (isSuccess(begin->digit, open->unique)) {	// ���׽�㼴ΪĿ��ڵ�, ֱ�ӽ���

		printf("\nsearch successful! \n");

		printf("�׽�㼴ΪĿ��ڵ�, �����ƶ�(�ƶ� 0 ������Ŀ��״̬). \n");

	}
	else {	// �׽���Ŀ��ڵ�

		bool isOk = Unknown;

		while (1) {	// Ѱ��Ŀ��ڵ�

			if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {	// ����������ż����ͬ, �����; ����, ����

				searchFollow(open, node);

			}

			if (isEmpty(open)) {	// (����)open��Ϊ��

				isOk = False;
				break;

			}

			node = deleteQ(open);

			if (isSuccess(node->digit, open->unique)) {	// ���ҵ��������, ������

				isOk = True;
				break;

			}

		}

		if (isOk == True) {

			printf("\nsearch successful! \n");

			int times = backtrack(node);

			printf("\n�����ƶ� %d ������Ŀ��״̬ \n", times);

		}
		else if (isOk == False) {

			printf("\nsearch failed! \n");
			printf("\nĿ��״̬���ɴ� \n");

		}

	}

}


void run(Qpointer open, Ipointer begin) {

	start = clock();

	handle(open, begin);

	stop = clock();

	double duration = (double)(stop - start) / CLK_TCK;

	printf("--------- breadth first search ---------\n");
	printf("��ʱ: %fs\n", duration);

}


Ipointer createNode(Ipointer nine) {	// �����ڵ�

	Ipointer node = (Ipointer)malloc(ISIZE);

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			node->digit[i][j] = nine->digit[i][j];

		}

	}

	node->zero[0] = nine->zero[0];
	node->zero[1] = nine->zero[1];

	return node;

}


bool move(Ipointer node, Direction way) {	// �ƶ� "0"

	int x, y;	// �洢 "0" �ĺᡢ������

	x = node->zero[0];
	y = node->zero[1];

	int mx = x;	// �ƶ����x����
	int my = y;	// �ƶ����y����

	bool flag = False;	// ����ܷ��ƶ�

	switch (way) {	// ѡ����

	case UP:
		if ((--mx) >= 0) {

			flag = True;

		}
		break;
	case DOWN:
		if ((++mx) <= 2) {

			flag = True;

		}
		break;
	case LEFT:
		if ((--my) >= 0) {

			flag = True;

		}
		break;
	case RIGHT:
		if ((++my) <= 2) {

			flag = True;

		}
		break;

	}

	if (flag == True) {	// ���ƶ�

		int location = node->digit[mx][my];	// ���н��Ԫ�ؽ���

		node->digit[x][y] = location;

		node->digit[mx][my] = 0;

		node->zero[0] = mx;	// ��ֵ���ڵ�"0"����
		node->zero[1] = my;

		node->blockDirection = getBlockDirection(way);	// ��ֵ���˷���

	}

	return flag;

}


void locateZeros(Ipointer node) {	// ��λ "0" ������, ֻ��ȷ����ʼ����"0"����ʱ, ����һ��

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] == 0) {

				node->zero[0] = i;
				node->zero[1] = j;

			}

		}

	}

}


Direction getBlockDirection(Direction way) {	// ��ȡ��ֹ�ƶ�����: �����ƶ��ķ�����

	Direction ok = NONE;

	switch (way) {	// ��ֹ����

	case UP:
		ok = DOWN;
		break;
	case DOWN:
		ok = UP;
		break;
	case LEFT:
		ok = RIGHT;
		break;
	case RIGHT:
		ok = LEFT;
		break;

	}

	return ok;

}


void searchFollow(Qpointer open, Ipointer begin) {	// Ѱ�Һ�̽ڵ�

	Ipointer node = NULL;

	for (Direction way = UP; way <= RIGHT; way++) {	// ���� "�ϡ��¡�����" �����ĸ�����, �ж��Ƿ���ƶ�

		if (way != begin->blockDirection) {	// �ǻ��˷���

			node = createNode(begin);	// ���ݸ��ڵ㴴���½ڵ�

			bool flag = move(node, way);	// �ƶ�"0", Ϊ�½ڵ�����²���

			if (flag == True) {	// ���ܹ������²���, ��, ���ƶ�

				node->parent = begin;	// ��ֵ����ָ��

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {
					addQ(open, node);

				}

			}

		}

	}

}


int backtrack(Ipointer end) {	// ����

	Ipointer p = end;

	int times = -1;	// ����

	while (p != NULL) {

		printf("--------- %d times start ---------\n", ++times);

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				printf("%3d", p->digit[i][j]);

			}

			printf("\n");

		}

		p = p->parent;

	}

	return times;

}


bool judgeParity(int begin, int open) {		// �ж��²����ľŹ�����������ĸ�������ż���Ƿ�һ��

	int i = begin % 2;
	int j = open % 2;

	if (i == j) {

		return True;

	}
	else {

		return False;

	}

}
