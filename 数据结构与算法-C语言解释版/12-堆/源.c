#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define NUM 10

/*
����������
	1.Ҫôû�к��ӣ�Ҷ�ӽڵ㣩Ҫô�����������ӣ������������һ�����ӵĽڵ�
	2.Ҷ�ӽڵ���ͬһ��
���ڵ�߶�Ϊ0�����ڵ����һ��߶�Ϊ1���Դ�����
�߶�Ϊm����һ��ڵ���Ϊ 2��m�η�
�߶�Ϊn�����������ڵ���Ϊ 2��n-1�η�
��ȫ��������
	��������һ�㣬�����ұ������ɾ�����ɽڵ�
	���������Խṹ�����飩������ȫ������
		�й��ɣ����ڵ��±�n���������±�2*n+1,���Һ����±�2*n+2
����ʽ�������������������
����ʽ�������������������
�ѣ�
	�������ȫ������
		��>�ӣ��󶥶ѣ����ѣ�=����
		��<�ӣ�С���ѣ���С�ѣ�=����

	�ѵĲ��룺
		1.��������ķ�ʽ�ӵ����
		2.��ʱ�洢��������
		3.����ѭ���������ڵ�����ǲ���ͻ�Ľڵ������
		4.ѭ������ ���ڵ㸲���ӽڵ�
		5.ѭ������������ʱ�洢�Ĵ������ݸ��ǵ�ǰ�ڵ�
	�ѵ�ɾ����
		1.��ʱ�����ɾ���ݣ��Ѷ�Ԫ�أ�
		2.�����������н�С���Ǹ�
		3.ѭ�����¹�λ������������
			��������������С���Ǹ���С��ѭ������
			Խ�磬ѭ������
		4.ѭ������ ��ǰ�ڵ��������������С�Ľ���
		5.ѭ��������len--
*/

struct Heap {
	int* pRoot;//ָ����ڵ��ָ��
	int curSize;
	int MaxSize;
};

//��ʼ��
void initHeap(struct Heap* h) {
	h->pRoot = NULL;
	h->curSize = 0;
	h->MaxSize = 0;
}
//����
void insertNode(struct Heap* h, int inData) {
	//���ж������Ƿ��ܲ���
	if (h->MaxSize <= h->curSize) {
		h->MaxSize = h->MaxSize + ((h->MaxSize / 2) > 1 ? (h->MaxSize / 2) : 1);
		int* pNew = malloc(h->MaxSize * sizeof(struct Heap));
		if (h->pRoot) {
			memcpy(pNew, h->pRoot, h->curSize * sizeof(struct Heap));
			free(h->pRoot);
		}
		h->pRoot = pNew;
	}
	//�ȴ����������
	if (0 == h->curSize) {
		h->pRoot[h->curSize++] = inData;
		return;
	}
	//��ʱ�洢��������
	int tempData = inData;
	//��ʱ�洢�����±꣨����ѭ���ã�
	int curIdx = h->curSize;
	int parentIdx;

	while (1)
	{
		if (curIdx % 2 == 1) {
			parentIdx = (curIdx - 1) / 2;
		}
		else {
			parentIdx = (curIdx - 2) / 2;
		}
		

		if (curIdx <= 0)break;
		if (h->pRoot[parentIdx] < inData)break;
		//���¸��ǣ����ڵ㸲���ӽڵ㣩
		h->pRoot[curIdx] = h->pRoot[parentIdx];
		curIdx = parentIdx;
	}
	h->pRoot[curIdx] = inData;
	h->curSize++;
}
//����
void travel(struct Heap* h) {
	printf("Heap��\n");
	for (int i = 0; i < h->curSize; i++)
	{
		printf("%2d ", h->pRoot[i]);
	}
	printf("\n");
}
//ɾ���Ѷ�
int delTop(struct Heap* h) {
	if (NULL == h)return -2;
	if (0 == h->curSize)return -1;
	if (1 == h->curSize) {
		h->curSize = 0;
		return h->pRoot[0];
	}
	//��ʱ�����ɾ����
	int temp = h->pRoot[0];
	//��ǰidx
	int curIdx = 0;
	//������������С���Ǹ���idx
	int minIdx;

	//���һ�����ݸ��ǶѶ�����
	h->pRoot[0] = h->pRoot[h->curSize - 1];
	while (1)
	{
		//�ж��Ƿ�Խ��
		if ((curIdx * 2 + 1) > h->curSize-1 ||
			(curIdx * 2 + 2) > h->curSize-1) {
			break;
		}
		//�ȼ�������������С��
		minIdx = curIdx * 2 + 1;
		//�����߲�����С�ģ��ͻ����ұߵ�
		if (h->pRoot[minIdx + 1] < h->pRoot[minIdx]) {
			minIdx++;
		}
		//�ж������ڶѶ��������Ƿ�Ҫ��minidx��С
		if (h->pRoot[h->curSize - 1] < h->pRoot[minIdx]) {
			break;
		}

		//��С�Ϳ�ʼ���ϸ���(�Ӹ��Ǹ����������ˣ��ø��Ǹ�ʡ��Դ)
		h->pRoot[curIdx] = h->pRoot[minIdx];
		
		//idx������
		curIdx = minIdx;

	}
	//ѭ������֮�����һ�����ݸ��ǵ�ǰλ��
	h->pRoot[curIdx] = h->pRoot[h->curSize - 1];
	//ɾ�����
	h->curSize--;
	return temp;
}


int main() {
	int arr[NUM] = { 12,66,39,48,53,72,99,1,9,41 };
	struct Heap h;
	initHeap(&h);

	for (int i = 0; i < NUM; i++)
	{
		insertNode(&h, arr[i]);
		travel(&h);
	}

	for (int i = 0; i < NUM; i++)
	{
		delTop(&h);
		travel(&h);
	}
	

	return 0;
}