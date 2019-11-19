#pragma once

#define NSIZE sizeof(struct Node)
#define QSIZE sizeof(struct Queue)
#define ISIZE sizeof(struct Nine)

#define CSIZE sizeof(struct Closed)

#define HSIZE sizeof(struct Helper)

#define MAXK 10e1  /* ���Ժ����ظ����õĴ��� */

clock_t start, stop;   /* ��ʼʱ�������ʱ�� */

typedef enum bool{   // �Խ�bool��

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


typedef struct Node {	/* ���ݽṹ: �����еĽ�� */

	ElementType Data;
	struct Node* Next;

} Node, * Npointer;


typedef struct Helper {	// ����handle�����Ľṹ��

	bool flag;
	Ipointer end;

} Helper, * Hpointer;

void helper(Hpointer helper, char name[]);

Hpointer store[3];	/* �洢���ֽ�� */


typedef struct Closed {	// ����ʵ��

	ElementType Data;
	struct Closed* Next;

} Closed, * Cpointer;

Cpointer createClosed();
void insertNode(Cpointer headp, Ipointer node);
Ipointer findUnique(Cpointer headp, Ipointer node);
void applyAStar(Cpointer closed, Ipointer node);	// Ӧ��A*�㷨

Cpointer getClosed(Ipointer begin);
void dostoryClosed(Cpointer headp);


typedef struct Queue {	// ����

	Npointer Front, Rear;    /* ��ͷ����βָ�� */
	int MAXSize;                   /* ����������� */
	int standard[3][3];	/* ��׼�Ź��� */
	int inversion;	  /* ��׼�Ź���������� */
	long unique;	/* ��׼�Ź��񲼾�ת����long�ʹ� */

} Queue, * Qpointer;


/* ------------------ queue function ------------------ */

Qpointer createQueue(int MAXSize, long unique, int inversion);	// ��������

bool isEmpty(Qpointer headp);	// �����п�

Qpointer addQ(Qpointer headp, ElementType X);	// ���

Ipointer deleteQ(Qpointer headp);	// �޸ĺ�ĳ��Ӳ���

void output(Qpointer headp);	// �����������������ʵ�����û��ʹ��; �������Ժ���

void destoryQ(Qpointer headp);	// ��ն���Ԫ��
/* ----------------------------------------------------- */



/* -------------------- main������� -------------------- */

Qpointer initialize();	// ��ʼ������

Ipointer input(Qpointer open);	// ���뺯��

Hpointer handle(Qpointer open, Ipointer begin, int order, Cpointer closed);	// ��Ҫ�������̺���

bool isSuccess(int sequence, int unique);	// �Ƿ�ɹ��ҵ���׼�Ź���

/* ----------------------------------------------------- */



/* ------------------- core function ------------------- */

long converseMatrix(const int(*nine)[3]);	// �Ź���--->����ת������

int countInverseNumber(long number);	// �����������ĸ���

long assistInverse(const int(*nine)[3]); // ���������������ڴ󲿷���ͬconverseMatrix, ������Ҫ�޸�

int countBit(long number);	// ��ѯ����λ��

void locateZeros(Ipointer node);	// ��λ�ڵ�node�ľŹ����� "0" ������

void breadthFirstSearchFollow(Qpointer open, Ipointer begin);	// Ѱ�Һ��

Ipointer generateNewLayout(Ipointer nine);	// �����µľŹ�����

bool move(Ipointer node, Direction way);	// �ƶ�

Direction getBlockDirection(Direction way);	// ��ȡ���˷���

bool judgeParity(int begin, int open);	// ��żУ��

int backtrack(Ipointer end);	// ����, �õ�����·��

/* --------------------------------------------------- */

void globalOptimizationFollow(Qpointer open, Ipointer begin);	// ȫ���Ż�

void weightSort(ElementType A[], int N);	// Ȩ������: ���ò�������

void getWeight(Qpointer open, Ipointer node);	// ��ȡȨ��

int getDeep(Ipointer node);	// ��ȡ���

void print(ElementType A[], int N);	// ������

void run(Qpointer open, Ipointer begin, int order, char name[], Cpointer closed);  /* ʱ����Ժ��� */

void processBlock(Qpointer open, Ipointer begin);	// �����: ��װʹ��
