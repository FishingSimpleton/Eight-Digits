#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"Header.h"

#pragma warning(disable:4996)

/**
*	��������,
	unique: ��׼�Ź���Ĳ���;
	inversion: ��׼�Ź����������;
	number: �Ѵ��ھŹ��񲼾�����;
	headp->nine[100]: �����洢�Ѿ����ڵľŹ��񲼾�;
	author: Sun Rui
	time: 2019.11.16
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
