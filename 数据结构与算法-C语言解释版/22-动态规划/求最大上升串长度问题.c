#include<stdio.h>
#include<malloc.h>
#include<string.h>

int main() {
	int N;
	printf("�������ַ������ȣ�");
	scanf("%d", &N);
	int* pBuff = malloc(sizeof(int) * N);
	printf("�������ַ������ÿո��������");
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &pBuff[i]);
	}
	//����һ����ʱ����
	int* pMaxLen = malloc(sizeof(int) * N);
	memset(pMaxLen, 0, sizeof(int) * N);

	int maxPos = 1;//�±�
	int nTemp;
	for (int i = 2; i < N; i++)//�ӵ�������ʼ������ĩβ
	{
		//ʵʱ��¼��ǰ�������������
		nTemp = 1;
		for (int j = 1; j < i; j++)//��pBuff[i]ǰ��Ĵ��������������
		{
			//�ұȵ�ǰ����С������
			if (pBuff[j] < pBuff[i]) {
				if (nTemp < pMaxLen[j]) {
					nTemp = pMaxLen[j];
				}
			}
			pMaxLen[i] = nTemp + 1;
			printf("i:%d,j:%d pMaxLen[%d]:%d\n", i, j, i, pMaxLen[i]);
		}
	}

	printf("��������Ӵ��ĳ���Ϊ��%d\n", pMaxLen[N - 1]);

	while (1);
	return 0;
}
