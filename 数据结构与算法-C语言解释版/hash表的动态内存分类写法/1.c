#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<malloc.h>

//����ڵ�����
struct Node {
	int data;
	struct Node* pNext;
};

//��������ڵ�ĺ���
struct Node* creatNode(int data) {
	struct Node* pNew = malloc(sizeof(struct Node));
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pNext = NULL;
	return pNew;
}

//��ϣ��
struct HashTable {
	struct Node**** arr;
};

//��ʼ����ϣ��ĺ���
void initHash(struct HashTable* phash) {
	if (NULL == phash)return;

	//��һ��
	phash->arr = malloc(10 * sizeof(struct Node***));
	//�ڶ���
	for (int i = 0; i < 10; i++)
	{
		phash->arr[i]= malloc(10 * sizeof(struct Node**));
	}
	//������
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			phash->arr[i][j] = malloc(10 * sizeof(struct Node*));

			//��ʼ��
			memset(phash->arr[i][j], 0, 10 * sizeof(struct Node*));
		}
	}
}
//�ͷ�hash��
void freeHash(struct HashTable* phash) {
	if (NULL == phash)return;
	if (NULL == phash->arr)return;
	//�ͷ����²�
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			free(phash->arr[i][j]);
		}
	}
	//�ͷŵڶ���
	for (int i = 0; i < 10; i++)
	{
		free(phash->arr[i]);
	}
	//�ͷŵ�һ��
	free(phash->arr);
}

//��hash���з����ݵĺ���
void push(struct HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	struct Node* pNew = creatNode(data);
	if (NULL == pNew)return NULL;

	//�õ�����λ�ϵ���
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	//���õ���Ӧλ���ϵ�ָ��
	struct Node* pTemp = phash->arr[bai][shi][ge];

	//�����Ƿ��Ѿ�������
	if (pTemp) {
		//β��
		while (pTemp->pNext)pTemp = pTemp->pNext;
		pTemp->pNext = pNew;
	}
	else {
		phash->arr[bai][shi][ge] = pNew;
	}
}

//����hash�������ݵĺ���
struct Node* find(struct HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	//�õ�����λ�ϵ���
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	struct Node* pTemp = phash->arr[bai][shi][ge];
	while (pTemp) {
		if (data == pTemp->data)return pTemp;
		pTemp = pTemp->pNext;
	}
	return NULL;

}

int main() {
	struct HashTable h;
	initHash(&h);

	int n;
	int data;
	bool isEnd = true;
	while (isEnd)
	{
		printf("1 - ����\n");
		printf("2 - ����\n");
		printf("3 - �˳�\n");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("������Ҫ��������� > ");
			scanf("%d", &data);
			push(&h, data);
			printf("������ϣ�\n");
			break;
		case 2:
			printf("������Ҫ���ҵ����� > ");
			scanf("%d", &data);
			struct Node* pTemp = find(&h, data);
			if (NULL == pTemp) {
				printf("û���ҵ���\n");
			}
			else {
				printf("�ҵ��ˣ�%d\n", pTemp->data);
			}
			break;
		case 3:
			freeHash(&h);
			isEnd = false;
			break;
		default:
			printf("�޴�ѡ�\n");
			break;
		}
	}

	return 0;
}
