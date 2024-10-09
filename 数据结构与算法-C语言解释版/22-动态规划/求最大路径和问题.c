#include<stdio.h>

int map[5][5] = {
	{ 9 },
	{ 4, 7 },
	{ 5, 3, 1 },
	{ 2, 4, 4, 1 },
	{ 7, 5, 3, 2, 4 }
};

int arr[5][5] = { 0 };
void init(int arr[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			arr[i][j] = -1;
	}
}

int Max(int a, int b) {
	return ((a > b) ? a : b);
}

//4 �ռ��Ż�
int getMax(int i, int j) {
	int temp[5];
	//���һ��ֱ�Ӹ�ֵ
	for (int i = 0; i < 5; i++)
	{
		temp[i] = map[4][i];
	}
	//һ�����ȥ ֻ��������
	for (int i = 3; i >= 0; i--)//��
	{
		for (int j = 0; j <= i; j++)
		{
			temp[j] = map[i][j] + Max(temp[j], temp[j + 1]);
		}
	}
	return temp[0];
}

/*
//3 ��ѭ��
int getMax(int i, int j) {
	//�������ϲ���

	//���һ��ֱ�Ӹ�ֵ
	for (int i = 0; i < 5; i++)
	{
		arr[4][i] = map[4][i];
	}
	//һ�����ȥ ֻ��������
	for (int i = 3; i >= 0; i--)//��
	{
		for (int j = 0; j <= i; j++)
		{
			arr[i][j] = map[i][j] + Max(arr[i + 1][j], arr[i + 1][j + 1]);
		}
	}
	return arr[0][0];
}
*/

/*
//2 ʡȥһЩû������ĵݹ� ����ʱ����洢�ķ�ʽ��ԼһЩ�ݹ�
int getMax(int i, int j) {
	if (-1 != arr[i][j])return arr[i][j];
	if (5 == i) {
		arr[i][j] == map[i][j];
	}
	else {
		int n = getMax(i + 1, j);
		int m = getMax(i + 1, j + 1);
		arr[i][j] = map[i][j] + Max(m, n);
	}
	return arr[i][j];
}
*/

/*
//1 ̰���㷨˼�� �ݹ鷽ʽʵ�� ��̫��
int getMax(int i, int j) {
	if (5 == i)return map[5][5];
	int n = getMax(i + 1, j);
	int m = getMax(i + 1, j + 1);

	return map[i][j] + Max(m, n);
}
*/
int main() {
	//init(arr);
	printf("%d\n", getMax(0, 0));
	//printf("count:%d\n", count);


	while (1);
	return 0;
}
