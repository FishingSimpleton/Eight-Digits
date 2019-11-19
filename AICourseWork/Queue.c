#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<string.h>
#include"Header.h"

#pragma warning(disable:4996)

/**
* queue operation
* author: Sun Ray 2019.11.19
*	��������,
*	unique: ��׼�Ź���Ĳ���;
*	inversion: ��׼�Ź����������;
*	number: �Ѵ��ھŹ��񲼾�����;
*	headp->nine[100]: �����洢�Ѿ����ڵľŹ��񲼾�;
*/
Qpointer createQueue(int MAXSize, long unique, int inversion) {

	Qpointer headp = NULL;
	headp = (Qpointer)malloc(QSIZE);
	headp->Front = headp->Rear = NULL;
	headp->MAXSize = MAXSize;
	headp->inversion = inversion;
	headp->unique = unique;

	return headp;

}


bool isEmpty(Qpointer headp) {

	return (headp->Front == NULL);

}


Qpointer addQ(Qpointer headp, ElementType X) {

	Npointer nodep = NULL;

	if (isEmpty(headp)) {

		nodep = (Npointer)malloc(NSIZE);
		nodep->Data = X;
		nodep->Next = NULL;
		headp->Front = nodep;
		headp->Rear = nodep;

	}
	else {

		nodep = (Npointer)malloc(NSIZE);      /*  pList list = (pList)malloc(sizeof(lis)); */
		nodep->Data = X;                      /*  list->element = element; */
		nodep->Next = NULL;
		headp->Rear->Next = nodep;            /*  list->next = queue->rear->next; */
		headp->Rear = headp->Rear->Next;      /*  queue->rear->next = list; */
											  /*  queue->rear = list; */

	}

	return headp;

}


Ipointer deleteQ(Qpointer headp) {

	Npointer Front = NULL;

	if (isEmpty(headp)) {

		printf("The Queue is empty!\n");

	}
	else {

		Front = headp->Front;

		if (headp->Front == headp->Rear) {    /* ��������ֻ��һ����� */

			headp->Front = headp->Rear = NULL;

		}
		else {

			headp->Front = headp->Front->Next;

		}

		//free(Front);	// ��ΪҪ��������·��, ����, �˴�ȡ��free()����

	}

	return Front->Data;	// ���س���Ԫ��

}


void output(Qpointer headp) {	// �������

	Npointer Front = headp->Front;

	printf("------------------ \n");

	while (Front != NULL) {

		for (int i = 0; i < 3; i++) {

			for (int j = 0; j < 3; j++) {

				printf("%3d", Front->Data->digit[i][j]);

			}

			printf("\n");

		}

		Front = Front->Next;

		printf("------------------ \n");

	}

}


void destoryQ(Qpointer headp) {	// ��ն����е�����Ԫ��

	Npointer front = NULL;

	Npointer last = NULL;

	front = headp->Front;

	while (!isEmpty(headp)) {

		if (headp->Front == headp->Rear) {    /* ��������ֻ��һ����� */

			headp->Front = headp->Rear = NULL;

		}
		else {

			headp->Front = headp->Front->Next;

		}

		last = front;

		front = front->Next;

		free(last);	// ��ΪҪ��������·��, ����, �˴�ȡ��free()����

	}

}
