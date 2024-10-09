#include<stdio.h>

int getMin(int a, int b) {
	return(a < b ? a : b);
}

int getMinPath(int map[5][5]) {
	//���ڴ洢�߹�ʱ��·��ֵ
	int dp[5][5] = { 0 };

	for (int i = 1; i < 5; i++)//����
	{
		for (int j = 1; j < 5; j++) {//����
			if (1 == i) {//ֻ�����д�������Ŀ���
				dp[i][j] = dp[i][j - 1] + map[i][j];
			}
			else if (1 == j) {//ֻ�����д��ϱ����Ŀ���
				dp[i][j] = dp[i - 1][j] + map[i][j];
			}
			else {//���ܴ��������Ҳ���ܴ��ϱ���
				dp[i][j] = getMin(dp[i][j - 1], dp[i - 1][j]) + map[i][j];
			}
		}
	}
	return dp[4][4];
}

int main() {
	int map[5][5] = {
		{ 0, 0, 0, 0, 0 },
		{ 0, 3, 6, 2, 1 },
		{ 0, 4, 3, 0, 6 },
		{ 0, 5, 5, 4, 3 },
		{ 0, 9, 7, 2, 8 }
	};

	printf("���·����:%d\n",getMinPath(map));

	while (1);
	return 0;
}
