#include<iostream>
#define N 10000//��������������Ҳ�����Լ��ĳ�malloc��ʽ

using namespace std;

int main() {
	int firstNum[N] = { 0 };
	int secondNum[N] = { 0 };
	int sum[N] = { 0 };
	//1.���������������ַ�ת��Ϊint
	string str1, str2;
	cin >> str1;
	//�ַ���ת�������ַ������飨˳������һ�£�
	for (int i = 0; i < str1.size(); i++)
	{
		//�� �����������Чλ����ĩβ�� �� �ַ����е����λ
		//����firstNum[0]��Ӧ�ľ��Ǹ�λ
		firstNum[str1.size() - 1 - i] = str1[i] - '0';
	}
	cin >> str2;
	for (int i = 0; i < str2.size(); i++)
	{
		secondNum[str2.size() - 1 - i] = str2[i] - '0';
	}

	//2.�ҳ��������������λ���Ƕ���
	int max = str1.size() > str2.size() ? str1.size() : str2.size();

	//3.�������λ������ѭ������ͬλ�������
	for (int i = 0; i < max; i++)
	{
		//����Ҫ����sum[i]����Ϊǰһλ���ܻ��λ
		sum[i] = sum[i] + firstNum[i] + secondNum[i];
		if (9 < sum[i]) {
			//�����һλ�����ִ���9��˵����10���ϣ�Ҫ��λ
			sum[i + 1] = sum[i] / 10;
			sum[i] = sum[i] % 10;
		}
	}
	//ȥ�����λǰ���0
	if (0 == sum[max]) {
		max--;
	}
	//�����λ��ʼ�����
	for (int i = max; i >= 0; i--)
	{
		cout << sum[i];
	}
	return 0;
}