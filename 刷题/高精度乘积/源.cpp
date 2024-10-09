#include<iostream>
#define N 10000

using namespace std;

int main() {
	int one[N] = { 0 };
	int two[N] = { 0 };
	int product[N] = { 0 };
	string strOne, strTwo;
	cin >> strOne;
	cin >> strTwo;
	for (int i = 0; i < strOne.size(); i++)
	{
		one[i] = strOne[strOne.size() - 1 - i] - '0';
	}
	for (int i = 0; i < strTwo.size(); i++)
	{
		two[i] = strTwo[strTwo.size() - 1 - i] - '0';
	}
	//		one
	//	x	two
	//-------------
	for (int i = 0; i < strTwo.size(); i++)//two
	{
		for (int j = 0; j < strOne.size(); j++)//one
		{
			//˫��ѭ���������治�ܱ�֤ product[i + j] �� û�� ��Ч����
			product[i + j] = product[i + j] + one[j] * two[i];
			//��λ
			if (9 < product[i + j]) {
				//˫��ѭ���������治�ܱ�֤ product[i + j + 1] �� û�� ��Ч����
				product[i + j + 1] = product[i + j + 1] + product[i + j] / 10;
				product[i + j] = product[i + j] % 10;
			}
		}
	}
	//��������λ��
	int length = strOne.size() + strTwo.size();
	//������λ����0����ôλ��--
	while (0 == product[length-1] && length > 1) {
		length--;
	}
	//�����λ��ʼ���
	for (int i = length-1; i >= 0; i--)
	{
		cout << product[i];
	}

	return 0;
}