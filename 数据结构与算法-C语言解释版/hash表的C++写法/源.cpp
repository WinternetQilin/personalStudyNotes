#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<malloc.h>
#include<vector>
using namespace std;

//����ڵ�����
struct Node {
	int data;
	struct Node* pNext;
};

//��������ڵ�ĺ���
struct Node* creatNode(int data) {
	struct Node* pNew = new Node;
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pNext = NULL;
	return pNew;
}

//��ϣ��
struct HashTable {
	vector<vector<vector<Node*>>> arr;
};

//��ʼ����ϣ��ĺ���
void initHash(HashTable* phash) {
	if (NULL == phash)return;
	//��һ��
	vector<vector<vector<Node*>>> ptemp1;
	phash->arr = ptemp1;
	//�ڶ���
	for (int i = 0; i < 10; i++)
	{
		vector<vector<Node*>> ptemp2;
		phash->arr.push_back(ptemp2);

		//������
		for (int j = 0; j < 10; j++)
		{
			vector<Node*> ptemp3;
			//˳���ʼ��
			for (int k = 0; k < 10; k++)
			{
				ptemp3.push_back(NULL);
			}
			phash->arr[i].push_back(ptemp3);
		}
	}
}

//�ͷ�hash��
void freeHash(HashTable* phash) {
	
}

//��hash���з����ݵĺ���
void push(HashTable* phash, int data) {
	if (NULL == phash)return;
	Node* pNew = creatNode(data);
	if (NULL == pNew)return;

	//�õ�����λ�ϵ���
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	//���õ���Ӧλ���ϵ�ָ��
	Node* pTemp = phash->arr[bai][shi][ge];

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
Node* find(HashTable* phash, int data) {
	if (NULL == phash)return NULL;
	//�õ�����λ�ϵ���
	int bai = data / 100 % 10;
	int shi = data / 10 & 10;
	int ge = data % 10;

	Node* pTemp = phash->arr[bai][shi][ge];
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
	struct Node* pTemp;
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
			pTemp = find(&h, data);
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


/*

if (NULL == phash)return;
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
*/





