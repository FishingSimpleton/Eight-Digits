#pragma once

#define NSIZE sizeof(struct Node)
#define QSIZE sizeof(struct Queue)
#define ISIZE sizeof(struct Nine)

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
	int zero[2];	// "0" �ĺᡢ�����꣺zero[0] = x(������); zero[1] = y(������);
	Direction blockDirection;	// ��ֹ����, ��ֹ�����γ���ѭ��
	struct Nine* parent;	// ���ڵ�ָ��

} Nine, * Ipointer;


typedef Ipointer ElementType;	// Ԫ��������ΪIpointer


typedef struct Node {	/* ���ݽṹ: �����еĽ�� */

	ElementType Data;
	struct Node* Next;

} Node, * Npointer;


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

/* ----------------------------------------------------- */



/* -------------------- main������� -------------------- */

Qpointer initialize();	// ��ʼ������

Ipointer input();	// ���뺯��

void handle(Qpointer open, Ipointer begin);	// ��Ҫ�������̺���

void run(Qpointer open, Ipointer begin);

bool isSuccess(int(*digit)[3], int unique);	// �Ƿ�ɹ��ҵ���׼�Ź���

/* ----------------------------------------------------- */



/* ------------------- core function ------------------- */

long converseMatrix(const int(*nine)[3]);	// �Ź���--->����ת������

int countInverseNumber(long number);	// �����������ĸ���

long assistInverse(const int(*nine)[3]); // ���������������ڴ󲿷���ͬconverseMatrix, ������Ҫ�޸�

int countBit(long number);	// ��ѯ����λ��

void locateZeros(Ipointer node);	// ��λ�ڵ�node�ľŹ����� "0" ������

void searchFollow(Qpointer open, Ipointer begin);	// Ѱ�Һ��

Ipointer createNode(Ipointer nine);	// �����Ź�����

bool move(Ipointer node, Direction way);	// �ƶ�

Direction getBlockDirection(Direction way);	// ��ȡ���˷���

bool judgeParity(int begin, int open);	// ��żУ��

int backtrack(Ipointer end);	// ����, �õ�����·��

/* --------------------------------------------------- */
