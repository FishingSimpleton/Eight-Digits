#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/*
 ����A�㷨(ȫ�������㷨)���A*�㷨
 author: Sun Rui
 time: 2019.11.19
 */
void handle(MinHpointer open, Ipointer begin) {	// ������

	Ipointer node = begin;

	Cpointer closed = getClosed(begin);

	if (isSuccess(node->digit, open->unique)) {	// ���׽�㼴ΪĿ��ڵ�, ֱ�ӽ���

		printf("\nsearch successful! \n");

		printf("�׽�㼴ΪĿ��ڵ�, �����ƶ�(�ƶ� 0 ������Ŀ��״̬). \n");

	}
	else {	// �׽���Ŀ��ڵ�

		bool isOk = Unknown;

		while (1) {	// Ѱ��Ŀ��ڵ�

			if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {	// ����������ż����ͬ, �����; ����, ����

				globalOptimizationFollow(open, node);

			}

			if (isHeapEmpty(open)) {	// (����)open��Ϊ��

				isOk = False;
				break;

			}

			node = deleteMin(open);

			applyAStar(closed, node);

			insertNode(closed, node);

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

		node->unique = converseMatrix(node->digit);

		node->blockDirection = getBlockDirection(way);	// ��ֵ���˷���

	} else {

		free(node);

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


void globalOptimizationFollow(MinHpointer open, Ipointer begin) {

	Ipointer node = NULL;

	int k = 0;

	for (Direction way = UP; way <= RIGHT; way++) {	// ���� "�ϡ��¡�����" �����ĸ�����, �ж��Ƿ���ƶ�

		if (way != begin->blockDirection) {	// �ǻ��˷���

			node = createNode(begin);	// ���ݸ��ڵ㴴���½ڵ�

			bool flag = move(node, way);	// �ƶ�"0", Ϊ�½ڵ�����²���

			if (flag == True) {	// ���ܹ������²���, ��, ���ƶ�

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {

					node->parent = begin;	// ��ֵ����ָ��

					getWeight(open, node);

					insertElement(open, node);

				}

			}

		}

	}

}


void getWeight(MinHpointer open, Ipointer node) {	// ��ȡȨ��, Ȩ��ԽС, Խ�ȴﵽĿ��״̬

	int diff = 0;	// ��¼��ͬԪ�ظ���

	int deep = 0;	// rootΪ 1 ��

	int weight = 0;

	Ipointer p = node;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] != open->standard[i][j]) {

				diff++;

			}

		}

	}

	deep = getDeep(node);

	weight = diff + deep;	// Ȩ��ԽС(��, ǳ + ��, ���Լǳ����ͬԪ��Խ��), ���ƶ�Խ��, ·��Խ��

	node->weight = weight;

}


int getDeep(Ipointer node) {

	Ipointer p = node;

	int times = 0;

	while (p != NULL) {

		p = p->parent;

		times++;

	}

	return times;

}


/**
 A* algorithm
 author: Sun Rui 2019.11.19
*/
void applyAStar(Cpointer closed, Ipointer node) {	// Ӧ��A*�㷨

	Ipointer resultp = findUnique(closed, node);

	if (resultp != NULL) {

		if (getDeep(resultp) > getDeep(node)) {

			resultp->parent = node->parent;
			resultp->weight = node->weight;	// �б�Ҫ����

		}

	}

	return;

}