#include<iostream>
#include<cstring>//�õ���memset
#define N 100//�Զ������鳤�ȣ�Ҳ���Լ��ĳ�malloc��̬����

using namespace std;

//�׳��õ�
//multiplier ����
//product �˻�
int mulOne[N] = { 0 };//����1
int moSize = 0;//����1���������λ��
int mulTwo[N] = { 0 };//����2
int mtSize = 0;//����2���������λ��
int product[N] = { 0 };//�˻�
int proSize = 0;//�˻����������λ��
//����õ�
int sum[N] = { 0 };//��
int sumSize = 0;//�����������λ��

//ͳ���Ѿ��׳˹���������2��ʼ����Ϊ1�������ֱ�����
int cnt = 2;

void jiecheng(int n) {
	//���if��������for�����Ż���
	if (n > cnt)cnt = n;//���ж��Ѿ��׳˹������ʹ�������Ĵ�С��ϵ
	for (int i = cnt; i <= n; i++)//��û�׳˹�������ʼ
	{
		//��n����mulTwo
		int temp = i;
		mtSize = 0;//ÿ�ζ�Ҫ���ã���Ȼ����Ĳ���
		while (temp)
		{
			mulTwo[mtSize++] = temp % 10;
			temp /= 10;
		}
		//��ʼ��ˣ��ȳ��꣬���ܽ�λ��
		//		one
		//	x	two
		//-------------
		for (int i = 0; i < mtSize; i++)//two
		{
			for (int j = 0; j < moSize; j++)//one
			{
				//˫��ѭ���������治�ܱ�֤ product[i + j] �� û�� ��Ч����
				product[i + j] = product[i + j] + mulOne[j] * mulTwo[i];
			}
		}
		//�����λ
		for (int i = 0; i < mtSize + moSize; i++)
		{
			if (9 < product[i]) {
				product[i + 1] = product[i + 1] + product[i] / 10;
				product[i] = product[i] % 10;
			}
		}
		//����˻���λ��
		int length = mtSize + moSize;
		while (0 == product[length - 1]) {
			length--;
		}
		proSize = length;
		//���˲����������product��mulOne
		for (int i = 0; i < proSize; i++)
		{
			mulOne[i] = product[i];
		}
		moSize = proSize;
		//���product�������´μ���洢���
		memset(product, 0, sizeof(product));
		proSize = 0;
	}
	//���յļ�������mulOne��
	//for (int i = 0; i < moSize; i++)
	//{
	//	cout << mulOne[moSize - 1 - i];
	//}
	//cout << endl;
}

void qiuhe(int sum[N], int mulOne[N]) {
	//�ҵ��������������λ��
	int max = moSize > sumSize ? moSize : sumSize;
	//Ҳ���Ȳ��ܽ�λ���
	for (int i = 0; i < max; i++)
	{
		sum[i] = sum[i] + mulOne[i];
	}
	//�����λ
	for (int i = 0; i < max; i++)
	{
		if (9 < sum[i]) {
			sum[i + 1] = sum[i + 1] + sum[i] / 10;
			sum[i] = sum[i] % 10;
		}
	}
	sumSize = max;
	if (0 == sum[sumSize - 1]) {
		sumSize--;
	}
	//for (int i = 0; i < sumSize; i++)
	//{
	//	//cout << sum[sumSize - 1 - i];
	//}
	//cout << endl;
}

int main() {
	int n;
	cin >> n;
	//���ʼ�Ľ׳˸���ֵ
	mulOne[0] = 1;
	moSize = 1;
	//��ʼ����
	for (int i = 1; i <= n; i++)
	{
		jiecheng(i);
		qiuhe(sum, mulOne);
	}
	//������ս��
	for (int i = 0; i < sumSize; i++)
	{
		cout << sum[sumSize - 1 - i];
	}
	return 0;
}