#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* ����: ��ͷ�ڵ������
* ��ŵ�����Ϊָ��Ź����ָ��
* author: Sun Ray 2019.11.19
*/
Cpointer createClosed() {

	Cpointer closed = (Cpointer)malloc(CSIZE);

	closed->Data = NULL;
	closed->Next = NULL;

	return closed;

}


void insertNode(Cpointer headp, Ipointer node) {

	Cpointer p = NULL;

	p = headp->Next;

	Cpointer newp = (Cpointer)malloc(CSIZE);

	newp->Data = node;

	newp->Next;

	headp->Next = newp;

	newp->Next = p;


}


Ipointer findUnique(Cpointer headp, Ipointer node) {

	Cpointer p = headp->Next;

	while (p != NULL) {

		if (node->unique == p->Data->unique) {	// ���ҵ���Ԫ��

			return p->Data;

		}

		p = p->Next;

	}

	return NULL;

}


Cpointer getClosed(Ipointer begin) {

	Cpointer closed = createClosed();

	insertNode(closed, begin);

	return closed;

}


void dostoryClosed(Cpointer headp) {	// �������, ����ͷ���

	Cpointer p = headp;

	Cpointer lastp = NULL;

	while (p->Next != NULL) {

		lastp = p;
		p = p->Next;

		free(lastp);

	}

}