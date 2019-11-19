#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* core function
* author: Sun Ray
*/

Hpointer handle(Qpointer open, Ipointer begin, int order, Cpointer closed) {	// ������

	Ipointer node = begin;

	Hpointer helper = (Hpointer)malloc(HSIZE);

	bool isOk;

	if (isSuccess(node->digit, open->unique)) {	// ���׽�㼴ΪĿ��ڵ�, ֱ�ӽ���

		isOk = Unknown;
		helper->flag = isOk;
		helper->end = begin;

		return helper;

	}
	else {	// �׽���Ŀ��ڵ�

		while (1) {	// Ѱ��Ŀ��ڵ�

			if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {	// ����������ż����ͬ, �����; ����, ����

				if (order == 0) {	// order == 0: ִ�п�����������㷨

					breadthFirstSearchFollow(open, node);

				}
				else if (order == 1 || order == 2) {	// order == 1: ִ��ȫ�����������㷨; order == 2: ִ��A*�㷨

					globalOptimizationFollow(open, node);

				}

			}

			if (isEmpty(open)) {	// (����)open��Ϊ��

				isOk = False;
				break;

			}

			node = deleteQ(open);	// ����

			if (order == 2) {	// ִ��A*�㷨

				applyAStar(closed, node);	// Ӧ��A*�㷨

			}

			insertNode(closed, node);	// ������: ע��˳��, ��Ӧ��A*�㷨, �ٽ�������������

			if (isSuccess(node->unique, open->unique)) {	// ���ҵ��������, ������

				isOk = True;
				break;

			}

		}

	}

	helper->flag = isOk;
	helper->end = node;

	return helper;

}


Ipointer generateNewLayout(Ipointer nine) {	// �����ڵ�

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


bool move(Ipointer node, Direction way) {	// ���ĺ���: �ƶ� "0"

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

		node->unique = converseMatrix(node->digit);

	}

	return flag;

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
