#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#include "Header.h"

#pragma warning(disable:4996)

int main() {

	MinHpointer minH;
	int maxSize;
	int cnt;
	int i, j;
	int a[1000];

	printf("��������С��������");
	scanf("%d", &maxSize);
	minH = createMinHeap(maxSize);

	printf("������Ԫ�صĸ�����");
	scanf("%d", &cnt);

	printf("������Ԫ�أ�");

	for (j = 1; j <= cnt; j++) {

		scanf("%d", &a[j]);
		minH->Data[j] = a[j];
		minH->Size++;

	}

	bulidHeap(minH);
	printf("\n��������С��Ϊ��\n");
	output(minH);


	printf("\n����Ԫ��9: \n");
	insert(minH, 9);

	output(minH);

	deleteMin(minH);
	printf("\nɾ�����Ԫ�غ������Ϊ: \n");
	output(minH);

	return 0;

}
