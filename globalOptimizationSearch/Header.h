#pragma once

#define MINDATA	1e-9	// �Ѷ�Ԫ��(a[0])����С��
#define ERROR -1
#define ESIZE sizeof(ElementType)
#define HSIZE sizeof(struct Heap)

typedef enum Status {

	False = 0,
	True

} Status;

typedef int ElementType;
typedef int bool;

typedef struct Heap {

	ElementType* Data;    /* �洢Ԫ�ص����� */
	int Size;           /* �ѵ�ǰԪ�صĸ��� */
	int Capacity;       /* �ѵ�������� */

} Heap, * Hpointer;

typedef Hpointer MinHpointer;

MinHpointer createMinHeap(int maxSize);
bool isFull(MinHpointer minH);
bool insert(MinHpointer minH, ElementType x);
bool isEmpty(MinHpointer minH);
ElementType deleteMin(MinHpointer minH);
void percDown(MinHpointer minH, int p);
void bulidHeap(MinHpointer minH);
void output(MinHpointer minH);
