#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include "Header.h"
#pragma warning(disable:4996)


/**
* sumΪ�������ĸ���
*/
int countInverseNumber(long number) { // 456

	int sum = 0;

	int bit = countBit(number); // 3 = countBit(456)

	int power = bit - 1; // 2

	long temp = number;

	while (temp != 0L) {

		int zero = (int)pow(10, power); // 10, 2

		long first = temp / zero;	// 456 / 100

		long follow = temp - first * zero;	// 456 - 4 * 100

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
* �ж��Ƿ�ɹ�
*/
bool isSuccess(int(*digit)[3], int unique) {	// �Ƿ��ҵ���׼�Ź���

	if (converseMatrix(digit) == unique) {

		return True;	// digit�Ź��񲼾� = ��׼�Ź���; �ɹ�

	}
	else {

		return False;

	}

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
