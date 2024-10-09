#include<stdio.h>

/*
����������20

��Ʒ��	A		B		C		D		E
�����	3		5		6		7		9
��ֵ��	2		8		7		4		1

*/
//��������
#define V 20
//��Ʒ����
#define N 5

struct WuPin {
	int w;//���
	int c;//��ֵ
};

struct WuPin wp[N] = {
	{ 3, 2 }, { 5, 8 }, { 6, 7 }, { 7, 4 }, {9,1}
};

int Max(int a, int b) {
	return ((a > b) ? a : b);
}

int main() {
	int temp[100] = { 0 };

	for (int i = 0; i < N; i++)//�������
	{
		for (int j = wp[i].w ; j <= V; j++)//����仯
		{
			//��¼��ǰ�������ֵ
			temp[j] = Max(temp[j], temp[j - wp[i].w] + wp[i].c);
			printf("i:%d j:%d temp[%d-%d]:%d,temp[%d]:%d\n",
				i, j, j, wp[i].w, temp[j - wp[i].w], j, temp[j]);
		}
	}
	printf("����ֵ:%d\n", temp[V]);

	while (1);
	return 0;
}
