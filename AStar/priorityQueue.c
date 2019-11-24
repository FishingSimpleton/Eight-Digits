#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/*
 author: Sun Rui
 time: 2019-11-23
*/
MinHpointer createMinHeap(int maxSize, long unique, int inversion) {	// ������С��

	MinHpointer minHeap = (MinHpointer)malloc(HSIZE);
	minHeap->data = (ElementType*)malloc((maxSize + 1) * ESIZE);
	minHeap->capacity = maxSize;
	minHeap->size = 0;

	Ipointer top = (Ipointer)malloc(ISIZE);
	top->blockDirection = Unknown;
	top->parent = NULL;
	top->zero[0] = top->zero[1] = 0;
	top->weight = MINDATA;

	minHeap->data[0] = top;   /* �ڱ���� */

	minHeap->unique = unique;
	minHeap->inversion = inversion;

	return minHeap;

}


bool isFull(MinHpointer minH) {	// ����

	return (minH->size == minH->capacity);

}


bool insertElement(MinHpointer minH, ElementType x) {    /* ���򾫼� */

	int i = 0;   /* ���������������һ������λ�� */

	if (isFull(minH)) {

		printf("min heap is full! \n");

		return False;

	}
	else {

		i = ++minH->size;

		for (; x->weight < minH->data[i / 2]->weight; i = i / 2) {

			minH->data[i] = minH->data[i / 2];

		}

		minH->data[i] = x;

		return True;

	}

}


bool isHeapEmpty(MinHpointer minH) {

	return (minH->size == 0);

}


ElementType deleteMin(MinHpointer minH) {      /* ���� */

	int parent, child;
	ElementType minItem, x;

	if (isHeapEmpty(minH)) {  /* �ն� */

		printf("min heap is empty. \n");
		return ERROR;

	}

	minItem = minH->data[1];    /* ȡ������㣬��СԪ�� */
	x = minH->data[minH->size--];     /* ȡ�����һ��Ԫ�� */

	for (parent = 1; parent * 2 <= minH->size; parent = child) {

		child = parent * 2;
		if ((child != minH->size) && (minH->data[child]->weight > minH->data[child + 1]->weight)) {   /* δ�������λ�����Һ��� < ���� */

			child++;    /* childָ�����ҽ���еĽ�Сֵ */

		}

		if (x->weight <= minH->data[child]->weight) {	/* �ҵ�����λ�� */

			break;

		}
		else {    /* X < minH->Data[child] */

			minH->data[parent] = minH->data[child];

		}

	}

	minH->data[parent] = x;

	return minItem;

}


void percDown(MinHpointer minH, int p) {	// ����

	int parent, child;
	ElementType x;

	x = minH->data[p];	// ÿ����ڵ�

	for (parent = p; parent * 2 <= minH->size; parent = child) {

		child = parent * 2;   /* ��ָ�������� */

		if ((child != minH->size) && (minH->data[child]->weight > minH->data[child + 1]->weight)) {

			child++;    /* ������ָ���С���� */

		}

		if (x->weight <= minH->data[child]->weight) {

			break;

		}
		else {

			minH->data[parent] = minH->data[child];

		}

	}

	minH->data[parent] = x;

}


void bulidHeap(MinHpointer minH) {	// ���Ѵ��ڵ�N��Ԫ�ذ���С�ѵ�Ҫ������һά������

	int i = 0;

	for (i = minH->size / 2; i >= 1; i--) {

		percDown(minH, i);

	}

}


void outputHeap(MinHpointer minH) {

	int i = 0;

	for (i = 1; i <= minH->size; i++) {

		printf("%4d", minH->data[i]->weight);

	}

}
