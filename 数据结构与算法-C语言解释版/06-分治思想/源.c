#include<stdio.h>
#include<stdbool.h>
#include<malloc.h>
#include<string.h>

#define NUM 11
#define AREA 1000
#define BUCKET_NUM 10

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

/*Ͱ���䣩����
	�����ݷֳ����ɷݣ�ÿһ���У�������������ʽ�������������
	�������ݶ�����λ����ÿһλ�ϵ����ֶ���0~9�����Կ��Էֳ�ʮ��Ͱ
	��Ϊ�м��������Ͱ�Ĵ�СӦ���������С
	ʮ��Ͱ���0~9������ȫ����ʼ��Ϊ-1
	��һ���ȿ���λ
		��λ�Ƕ��٣��ͷŵ���Ӧ��ŵ���ͬ������
		��˳�Ŵ�Ͱ��ȡ������ԭ������
	�ڶ��ο�ʮλ
		����ȡ��ԭ��ͬ��
	�����ο���λ
		����ȡ��ԭ��ͬ��
	�������

*/
void bucket_sort(int arr[NUM], int len) {
	//ѭ��n��
	int area = 1;
	while (area<AREA)
	{
		int data;
		//׼��ʮ��Ͱ(��ά����)
		int* pArr = malloc(sizeof(int) * (BUCKET_NUM * NUM));
		//ȫ����ʼ��Ϊ-1
		memset(pArr, -1, sizeof(int) * (BUCKET_NUM * NUM));
		//���鵽Ͱ��
		for (int i = 0; i < len; i++)
		{
			data = arr[i] / area % 10;//���������Ϊ��ά������±�
			pArr[data * NUM + i] = arr[i];
		}
		//���鵽Ͱ��
		for (int i = 0,k=0; i < BUCKET_NUM*NUM; i++)
		{
			if (-1 != pArr[i]) {
				arr[k++] = pArr[i];
			}
		}
		travel(arr, NUM, false);
		area *= 10;
	}
}

/*���ֲ���
	һ���ų�һ��
*/
int halfFind(int arr[NUM], int len, int data) {
	//�ҵ��˷���Ԫ���±꣬�Ҳ�������-1
	//����±�
	int left = 0;
	//�ұ��±�
	int right = len - 1;
	//�м��±�
	int m = (left + right) / 2;
	while (true)
	{
		if (left > right) {
			return -1;
		}
		if (data == arr[m]) {
			//�ҵ���
			return m;
		}
		if (data > arr[m]) {
			left = m + 1;
			m = (left + right) / 2;
		}
		if(data < arr[m]){
			right = m - 1;
			m = (left + right) / 2;
		}
	}

}

/*��������
	�����ݷֳ������������
	�ȼٶ�һ���м�����
	����ٶ���ߵ�ʱ�м����ݣ���ô��Ų���ұߵ���
	����ߵĶ�Ҫ���м�����С���ұߵĶ����м����ݴ�
	���еݹ�
	����ټ������飬�ұ��ټ�������
	�ֵ�ÿ��ֻ��һ������ʱ�������������
	���岽��
		1.��ʱ�����м�����
		2.�����>��&&��>�м䣺����ǰŲ��һλ
			�������Ҹ�����
			����<��&&��<�м�ֵ��������Ų��һλ
			�������󸲸���
		ֱ�������Һ�£������ʱ������м�ֵ���ǲ�����ѭ��
			����>�ң�ѭ������
*/

void quickSort(int arr[NUM], int left, int right) {
	//��������
	if (left >= right) {
		return;
	}
	printf("left:%d  right:%d\n", left, right);
	//��ʱ�����м�����
	int temp = arr[left];
	//������������������left��right
	int L = left;
	int R = right;
	//ѭ��ֱ��left��right��£
	while (L < R) {
		while (L<R && arr[R]>temp) {
			R--;
		}
		arr[L] = arr[R];
		while (L < R && arr[L] < temp) {
			L++;
		}
		arr[R] = arr[L];
	}
	arr[L] = temp;
	travel(arr, NUM, false);
	//��ߵĵݹ�
	quickSort(arr, left, L - 1);
	//�ұߵĵݹ�
	quickSort(arr, L + 1, right);
}

void quick_sort(int arr[NUM], int len) {
	quickSort(arr, 0, len - 1);
}


int main() {
	int arr[NUM] = { 999,327,666,114,514,321,250,888,168,110,985 };
	travel(arr, NUM, false);

	//printf("Ͱ���䣩����\n");
	//bucket_sort(arr, NUM);

	printf("��������\n");
	quick_sort(arr, NUM);

	travel(arr, NUM, true);

	//����������
	//int n;
	//���
	//int ret;
	//while (true)
	//{
	//	printf("������Ҫ���ҵ����ݣ�");
	//	scanf("%d", &n);
	//	ret = halfFind(arr, NUM, n);
	//	if (ret < 0) {
	//		printf("û�ҵ� %d �����\n", n);
	//	}
	//	else {
	//		printf("arr[%d]:%d\n", ret, arr[ret]);
	//	}
	//}

	return 0;
}