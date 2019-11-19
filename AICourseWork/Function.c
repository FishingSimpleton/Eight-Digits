#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include "Header.h"
#pragma warning(disable:4996)


/**
* assist function
* author: Sun Ray 2019.11.19
*/
int countInverseNumber(long number) { // return: sumΪ�������ĸ���

	int sum = 0;

	int bit = countBit(number);

	int power = bit - 1;

	long temp = number;

	while (temp != 0L) {

		int zero = (int)pow(10, power);

		long first = temp / zero;

		long follow = temp - first * zero;

		long sub = follow;

		while (sub != 0) {

			if (first > (sub % 10)) {

				sum++;

			}

			sub /= 10;

		}

		temp = follow;

		power--;

	}

	return sum;

}


long assistInverse(const int(*nine)[3]) {	// �������������������ں� converseMatrix ̫������, �л���ῼ���ع�

	long number = 0L;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			int temp = nine[i][j];

			if (temp != 0) {

				number = number * 10 + temp;

			}

		}

	}

	return number;

}


int countBit(long number) {	// ��������λ��

	int bit = 0;

	while (1) {

		if (number % 10 != 0) {

			number = number / 10;
			bit++;

		}
		else {

			break;

		}

	}

	return bit;

}


/**
* �Ź��� ---> long�ʹ�
* ps: ʵ����ת�����ַ��͸���׳��
*/
long converseMatrix(const int(*nine)[3]) {	// ���Ź������(��ά����), �����ҡ����ϵ���, ת��Ϊһ������

	long number = 0L;

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			int temp = nine[i][j];	// ע���˴�temp����Ҫ�ܹ�ȡ�� "0", ����, һ������; �����ж����� if (temp != 0) X: ����ش�

			number = number * 10 + temp;

		}

	}

	return number;

}


bool judgeParity(int begin, int open) {		// �ж��²����ľŹ�����������ĸ�������ż���Ƿ�һ��

	int i = begin % 2;
	int j = open % 2;

	if (i == j) {

		return True;

	}
	else {

		return False;

	}

}


/**
* �ж��Ƿ�ɹ�
*/
bool isSuccess(int sequence, int unique) {	// �Ƿ��ҵ���׼�Ź���

	if (sequence == unique) {

		return True;	// digit�Ź��񲼾� = ��׼�Ź���; �ɹ�

	}
	else {

		return False;

	}

}


void locateZeros(Ipointer node) {	// ��λ "0" ������, ֻ��ȷ����ʼ����"0"����ʱ, ����һ��

	for (int i = 0; i < 3; i++) {

		for (int j = 0; j < 3; j++) {

			if (node->digit[i][j] == 0) {

				node->zero[0] = i;
				node->zero[1] = j;

			}

		}

	}

}