#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

/**
* ���ֲ��������ļ�������static�ļ�����
* author: Sun Ray
*/
int main() {

	Qpointer open = initialize();

	Ipointer begin = input(open);

	processBlock(open, begin);

	return 0;

}
