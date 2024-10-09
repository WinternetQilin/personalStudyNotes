#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<stdlib.h>
#define NUM 10

void travel(int arr[NUM], int len, bool isAfter) {
	if (isAfter) {
		printf("after sort:");
	}
	else {
		printf("before sort:");
	}

	for (int i = 0; i < len; i++)
	{
		printf("%02d ", arr[i]);
	}

	printf("\n");
}

/*ѡ������
	�Ӵ���������ѡһ����С�ķŵ���һ��λ��
	����߾�������������
	�ٴӴ�������������С�ģ��ŵ����������к��ʵ�λ�ã�ѭ�������ȴ�С��
	��������ѡ n-1 �ξ�������
*/
void select_sort(int arr[NUM], int len) {
	//ѡ n-1 ��
	for (int i = 0; i < len-1; i++)
	{
		//�Ӵ��ŷ�Χ���ҳ���С�ģ��ŵ����ʷ�Χ
		//���ŷ�Χ��i ~ len-1
		//����λ�ã�arr[i]

		//�ȼ�����������еĵ�һ����С
		int minIdx=i;
		for (int j = i; j < len; j++) {
			if (arr[j] < arr[minIdx]) {
				minIdx = j;
			}
		}
		if (arr[minIdx] < arr[i]) {
			int temp = arr[minIdx];
			arr[minIdx] = arr[i];
			arr[i] = temp;
		}
		printf("�� %d ��:", i + 1);
		travel(arr, NUM, false);
	}
}

/*��������
	ֱ�Ӱ��������鿴��������
	��߰�����һ��Ԫ�أ����������鲿�֣�һ��������Ȼ����
	�ұ߰��� n-1 ��Ԫ�أ��Ǵ�������
	ÿ�ν����������еĵ�һ�������뵽���������У�������󱣳�����
	��β��룺
		1.��ʱ�洢��������
		2.�Ӵ�������ǰһ����ʼ�Ƚϣ�һֱ��index=0
		3.���ǰһ�����ݱȴ������ݴ󣬽������󸲸ǣ�Ҳ����ֱ������������������������ʡһЩ�������裩
		4.�����ȴ������ݴ�ѭ������
		5.����ʱ���ݸ��ǽ���λ�õĺ�һ��λ��

*/
void insert_sort(int arr[NUM], int len) {
	for (int i = 1; i < len; i++)
	{
		//�������ݴ�����ʱ����
		int temp = arr[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			//���ǰһ�������ڴ����������󸲸�
			if (arr[j] > temp) {
				arr[j + 1] = arr[j];
			}
			else {
				break;
			}
			
		}
		//����ʱ���ݸ��ǽ���λ�õĺ�һ��λ��
		arr[j + 1] = temp;

		printf("�� %d ��:", i + 1);
		travel(arr, NUM, false);
	}
}

/*ϣ������
	���벽�����ÿ�ΰ��ղ���������
	����һ��Ĭ��ΪԪ�ظ�����һ��
	����Ϊ���ͷֳɼ���
	���10��Ԫ�أ���ô����Ϊ5
	i=0��i=5 Ϊһ�飬�Դ����ƣ���������������
	���Ų����ټ���һ�룬������Ϊ2
	i=0,i=2,4,6,8 Ϊһ�飬�Դ����ƣ���������������
	��󲽳�Ϊ1����������������
*/
void shell_sort(int arr[NUM], int len) {
	//������һ��ʼ��Ԫ�ظ�����һ��
	int step = len / 2;
	while (step)
	{
		//ÿ�ΰ��ղ������� ��������������
		for (int i = step; i < len; i++)
		{
			int temp = arr[i];
			int j;
			for (j = i - step; j >= 0; j-=step) {
				if (arr[j] > temp) {
					arr[j + step] = arr[j];
				}
				else {
					break;
				}

			}
			arr[j + step] = temp;
		}
		printf("step��%d����", step);
		travel(arr, NUM, false);
		//ÿ�α��ԭ����һ��
		step /= 2;
	}
}

/*��������
	�����㷨�����ģ�û��֮һ
	ʱ�临�Ӷ�ΪO��n�����Ҳ���Ҫ�Ƚ�
	�������ݣ����������±���Ȼ�������������������
	���ƣ�
		1.ֻ��������
		2.�������ظ�
		3.ʱ�临�Ӷȿɸ߿ɵ�
	1.�����ڴ洴��һ�����飬ʹ������±���Դ����������������
	2.��-1������Ҳ�����������ģ�
	3.��Ԫ�طŵ��������Ӧ��ͬ�±��λ��
	4.�ٱ�����Ϊ-1��Ԫ�أ��Ż�ԭ���飬�������
*/
void radix_sort(int arr[NUM], int len,int max) {
	//�����ڴ�
	int* pTemp = malloc(sizeof(int) * (max + 1));
	//ȫ����ʼ��Ϊ-1
	for (int i = 0; i < max + 1; i++) {
		pTemp[i] = -1;
	}
	//����������Ԫ�طŵ���Ӧ�±�λ��
	for (int i = 0; i < len; i++) {
		pTemp[arr[i]] = arr[i];
	}
	//������ʱ�ڴ棬��Ϊ-1�͸��ǻش�������
	int k = 0;
	for (int i = 0; i < max+1; i++)
	{
		if (-1 != pTemp[i]) {
			arr[k++] = pTemp[i];
		}
	}
}

int main() {
	int arr[NUM] = { 12,66,39,48,53,72,99,1,9,41 };
	travel(arr, NUM, false);
	//printf("ѡ������\n");
	//select_sort(arr, NUM);

	//printf("��������\n");
	//insert_sort(arr, NUM);

	//printf("ϣ������\n");
	//shell_sort(arr, NUM);

	printf("��������\n");
	radix_sort(arr, NUM,99);
	travel(arr, NUM, true);
	return 0;
}
