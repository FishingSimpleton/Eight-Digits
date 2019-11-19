#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* ȫ���������� algorithm
* author: Sun Ray 2019.11.19
*/
void globalOptimizationFollow(Qpointer open, Ipointer begin) {

	Ipointer node = NULL;

	Ipointer weight[4] = { NULL };

	int k = 0;

	for (Direction way = UP; way <= RIGHT; way++) {	// ���� "�ϡ��¡�����" �����ĸ�����, �ж��Ƿ���ƶ�

		if (way != begin->blockDirection) {	// �ǻ��˷���

			node = generateNewLayout(begin);	// ���ݸ��ڵ㴴���½ڵ�

			bool flag = move(node, way);	// �ƶ�"0", Ϊ�½ڵ�����²���

			if (flag == True) {	// ���ܹ������²���, ��, ���ƶ�

				if (judgeParity(countInverseNumber(assistInverse(node->digit)), open->inversion)) {

					node->parent = begin;	// ��ֵ����ָ��

					getWeight(open, node);

					weight[k++] = node;

				}

			}

		}

	}

	weightSort(weight, k);	// ����������Ȩ������

	for (int i = 0; i < k; i++) {	// ����������ֵ�Ĵ�С˳�������

		addQ(open, weight[i]);

	}

}


void getWeight(Qpointer open, Ipointer node) {	// ��ȡȨ��, Ȩ��ԽС, Խ�ȴﵽĿ��״̬

	int diff = 0;	// ��¼��ͬԪ�ظ���

	int deep = 0;	// rootΪ 1 ��

	int weight = 0;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] != open->standard[i][j]) {

				diff++;

			}

		}

	}

	deep = getDeep(node);

	weight = diff + deep;	// ��������: Ȩ��ԽС(��, ǳ + ��, ���Խǳ����ͬԪ��Խ��), ���ƶ�Խ��, ·��Խ��

	node->weight = weight;

}


void weightSort(ElementType A[], int N) {	// Ȩ������: ��������

	int p, i;
	ElementType temp;

	for (p = 1; p < N; p++) {

		temp = A[p];  /* ȡ��δ�������еĵ�һ��Ԫ�� */

		for (i = p; i > 0 && A[i - 1]->weight > temp->weight; i--) {  /* �����������������е�Ԫ�رȽϲ����� */

			A[i] = A[i - 1];

		}

		A[i] = temp;  // �ҵ�����λ�ã�����

	}

}


int getDeep(Ipointer node) {	// ��ȡ������

	Ipointer p = node;

	int times = 0;

	while (p != NULL) {

		p = p->parent;

		times++;

	}

	return times;

}