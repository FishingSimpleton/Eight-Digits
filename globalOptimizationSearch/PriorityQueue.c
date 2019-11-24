#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)


MinHpointer createMinHeap(int maxSize) {	// ������С��

	MinHpointer minHeap = (MinHpointer)malloc(HSIZE);
	minHeap->Data = (ElementType*)malloc((maxSize + 1) * ESIZE);
	minHeap->Capacity = maxSize;
	minHeap->Size = 0;
	minHeap->Data[0] = MINDATA;   /* �ڱ���� */

	return minHeap;

}


bool isFull(MinHpointer minH) {	// ����

	return (minH->Size == minH->Capacity);

}


bool insert(MinHpointer minH, ElementType x) {    /* ���򾫼� */

	int i = 0;   /* ���������������һ������λ�� */

	if (isFull(minH)) {

		printf("min heap is full! \n");

		return False;

	}
	else {

		i = ++minH->Size;

		for ( ; x < minH->Data[i / 2]; i = i / 2) {

			minH->Data[i] = minH->Data[i / 2];

		}

		minH->Data[i] = x;

		return True;

	}

}


bool isEmpty(MinHpointer minH) {

	return (minH->Size == 0);

}


ElementType deleteMin(MinHpointer minH) {      /* ���� */

	int parent, child;
	ElementType minItem, x;

	if (isEmpty(minH)) {  /* �ն� */

		printf("min heap is empty. \n");
		return ERROR;

	}

	minItem = minH->Data[1];    /* ȡ������㣬��СԪ�� */
	x = minH->Data[minH->Size--];     /* ȡ�����һ��Ԫ�� */

	for (parent = 1; parent * 2 <= minH->Size; parent = child) {

		child = parent * 2;
		if ((child != minH->Size) && (minH->Data[child] > minH->Data[child + 1])) {   /* δ�������λ�����Һ��� < ���� */

			child++;    /* childָ�����ҽ���еĽ�Сֵ */

		}

		if (x <= minH->Data[child]) {	/* �ҵ�����λ�� */

			break;

		} else {    /* X < minH->Data[child] */

			minH->Data[parent] = minH->Data[child];

		}

	}

	minH->Data[parent] = x;

	return minItem;

}


void percDown(MinHpointer minH, int p) {	// ����

	int parent, child;
	ElementType x;

	x = minH->Data[p];	// ÿ����ڵ�

	for (parent = p; parent * 2 <= minH->Size; parent = child) {

		child = parent * 2;   /* ��ָ�������� */

		if ((child != minH->Size) && (minH->Data[child] > minH->Data[child + 1])) {

			child++;    /* ������ָ���С���� */

		}

		if (x <= minH->Data[child]) {

			break;

		}
		else {

			minH->Data[parent] = minH->Data[child];

		}

	}

	minH->Data[parent] = x;

}


void bulidHeap(MinHpointer minH) {	// ���Ѵ��ڵ�N��Ԫ�ذ���С�ѵ�Ҫ������һά������

	int i = 0;

	for (i = minH->Size / 2; i >= 1; i--) {

		percDown(minH, i);

	}

}


void output(MinHpointer minH) {

	int i = 0;

	for (i = 1; i <= minH->Size; i++) {

		printf("%4d", minH->Data[i]);

	}

}
