#pragma once

#define NSIZE sizeof(struct Node)
#define QSIZE sizeof(struct Queue)
#define ISIZE sizeof(struct Nine)

#define CSIZE sizeof(struct Closed)

#define MINDATA	1e-9	// �Ѷ�Ԫ��(a[0])����С��
#define ERROR -1
#define MAXCAPACITY 1e5	// ���������
#define ESIZE sizeof(ElementType)
#define HSIZE sizeof(struct Heap)

clock_t start, stop;   /* ��ʼʱ�������ʱ�� */

typedef enum bool {   // �Խ�bool��

	False = 0,
	True,
	Unknown

} bool;


typedef enum Direction {   // ���ݽṹ: �ƶ��ķ���

	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE

} Direction;


typedef struct Nine {	// ���ݽṹ: �Ź���

	int digit[3][3];	// �Ź�������
	long unique;	// �Ź���ת����õ�������
	int zero[2];	// "0" �ĺᡢ�����꣺zero[0] = x(������); zero[1] = y(������);
	Direction blockDirection;	// ��ֹ����, ��ֹ�����γ���ѭ��
	struct Nine* parent;	// ���ڵ�ָ��
	int weight;	// �ڵ�Ȩ��

} Nine, * Ipointer;


typedef Ipointer ElementType;	// Ԫ��������ΪIpointer


typedef struct Heap {	// ��С��

	ElementType* data;    /* �洢Ԫ�ص����� */
	int size;           /* �ѵ�ǰԪ�صĸ��� */
	int capacity;       /* �ѵ�������� */
	int standard[3][3];	/* ��׼�Ź��� */
	int inversion;	  /* ��׼�Ź���������� */
	long unique;	/* ��׼�Ź��񲼾�ת����long�ʹ� */

} Heap, * Hpointer;

typedef Hpointer MinHpointer;

typedef struct Closed {	// ����ʵ��

	ElementType data;
	struct Closed* next;

} Closed, * Cpointer;


void insertNode(Cpointer headp, Ipointer node);
Ipointer findUnique(Cpointer headp, Ipointer node);
void applyAStar(Cpointer closed, Ipointer node);	// Ӧ��A*�㷨

Cpointer getClosed(Ipointer begin);
bool isListEmpty(Cpointer headp);



/* -------------------- main������� -------------------- */

MinHpointer initialize();	// ��ʼ������

Ipointer input(MinHpointer open);	// ���뺯��

void handle(MinHpointer open, Ipointer begin);	// ��Ҫ�������̺���

void run(MinHpointer open, Ipointer begin);	// �����

bool isSuccess(int(*digit)[3], int unique);	// �Ƿ�ɹ��ҵ���׼�Ź���

/* ----------------------------------------------------- */



/* ------------------- core function ------------------- */

long converseMatrix(const int(*nine)[3]);	// �Ź���--->����ת������

int countInverseNumber(long number);	// �����������ĸ���

long assistInverse(const int(*nine)[3]); // ���������������ڴ󲿷���ͬconverseMatrix, ������Ҫ�޸�

int countBit(long number);	// ��ѯ����λ��

void locateZeros(Ipointer node);	// ��λ�ڵ�node�ľŹ����� "0" ������

Ipointer createNode(Ipointer nine);	// �����Ź�����

bool move(Ipointer node, Direction way);	// �ƶ�

Direction getBlockDirection(Direction way);	// ��ȡ���˷���

bool judgeParity(int begin, int open);	// ��żУ��

int backtrack(Ipointer end);	// ����, �õ�����·��

/* --------------------------------------------------- */

void globalOptimizationFollow(MinHpointer open, Ipointer begin);	// ȫ���Ż�

void getWeight(MinHpointer open, Ipointer node);	// ��ȡȨ��

int getDeep(Ipointer node);	// ��ȡ���

/* ------------------- priority queue ------------------- */

MinHpointer createMinHeap(int maxSize, long unique, int inversion);
bool isFull(MinHpointer minH);
bool insertElement(MinHpointer minH, ElementType x);
bool isHeapEmpty(MinHpointer minH);
ElementType deleteMin(MinHpointer minH);
void percDown(MinHpointer minH, int p);
void bulidHeap(MinHpointer minH);
void outputHeap(MinHpointer minH);
