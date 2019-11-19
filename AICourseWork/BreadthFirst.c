#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


/**
* ����������� algorithm
*/
void breadthFirstSearchFollow(Qpointer open, Ipointer begin) {	// Ѱ�Һ�̽ڵ�

	Ipointer node = NULL;

	for (Direction way = UP; way <= RIGHT; way++) {	// ���� "�ϡ��¡�����" �����ĸ�����, �ж��Ƿ���ƶ�

		if (way != begin->blockDirection) {	// �ǻ��˷���

			node = generateNewLayout(begin);	// ���ݸ��ڵ㴴���½ڵ�

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
