#include<stdio.h>
#include<stdbool.h>

//�ʺ����
#define N 4

//��¼�ж����ְڷŷ�ʽ�����еĽⷨ��
int cnt = 0;

void travel(int Q[N][N]) {
	printf("------------------------------------\n");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%d ", Q[i][j]);
		}
		printf("\n");
	}
}

//�ܷŷ���true ���򷵻�false
bool isPlace(int x, int y, int Q[N][N]) {
	//�˸����� ȫ������0 �Ϳ��Է� �����ܷ�
	//�������ų������жϲ��ܷŵ����

	//�ж�б����Ҫ�õ���
	int xx;//x��
	int yy;//y��

	//�ж����� ����
	for (int i = 0; i < N; i++)
	{
		if (1 == Q[x][i] && y != i) return false;
	}
	//�ж����� ����
	for (int i = 0; i < N; i++)
	{
		if (1 == Q[i][y] && x != i) return false;
	}
	//�ж�����
	for (xx = x - 1, yy = y - 1; xx >= 0 && yy >= 0; xx--, yy--) {
		if (1 == Q[xx][yy])return false;
	}
	//�ж�����
	for (xx = x + 1, yy = y - 1; xx < N && yy >= 0; xx++, yy--) {
		if (1 == Q[xx][yy])return false;
	}
	//�ж�����
	for (xx = x - 1, yy = y + 1; xx >= 0 && yy < N; xx--, yy++) {
		if (1 == Q[xx][yy])return false;
	}
	//�ж�����
	for (xx = x + 1, yy = y + 1; xx < N && yy < N; xx++, yy++) {
		if (1 == Q[xx][yy])return false;
	}

	return true;
}

//exist=�Ѿ����ڵĻʺ�����
void queen(int exist, int Q[N][N]) {
	//�Ѿ��ں���N���ʺ󣬼�¼һ�γɹ��İڷ�
	if (N == exist) {
		travel(Q);
		cnt++;
		return;
	}

	//��û�ں�
	for (int i = 0; i < N; i++)//y���꣬����Ҫx���꣬��Ϊ�ʺ������֣�һ�в����ܷ�����
	{
		if (isPlace(exist, i, Q)) {//�ܷ�
			Q[exist][i] = 1;//��
			queen(exist+1, Q);//����һ��
			Q[exist][i] = 0;//���������ˣ�

		}
	}
}

int main() {
	//��������
	int Q[N][N] = { 0 };//0=û�зŻʺ�	1=�Żʺ�

	queen(0, Q);

	printf("%d�ʺ�������%d�ֽⷨ!\n", N, cnt);

	while (1);
	return 0;
}
