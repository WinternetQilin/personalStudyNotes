#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*
* 07
* 
hash����ϣ��/ɢ�б�/ɢ�з���

��Ϊ���ݽṹ���ԣ�����Ч�ʷǳ���

��Ϊ�㷨���ԣ������㷨

��ϣ��Ҫ�أ�
1.���ݵķ�Χ
	ȷ�������ݵĹ���ʽ ��ΧҲ����ȷ��
2.���ʵ�hash����
	�������ݵĵ�ַ�ĺ����������ݵķ�ʽ
3.�����ͻ�İ취
	��׳�Կ��ǣ�������ࣺhash��������һ�������ݣ�Ҫ�а취����

���蹹��һ��hash������ 1000���� ������

ʮ�������� ÿ��λ�ϵ����� 0-9

*/

//�����ͻ ������

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
	struct Node* arr[10][10][10];
};

//��ʼ����ϣ��ĺ���
void initHash(struct HashTable* phash) {
	if (NULL == phash)return;
	memset(phash->arr, 0, sizeof(phash->arr));
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
	while (true)
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
				printf("�ҵ��ˣ�%d\n",pTemp->data);
			}
			break;
		case 3:
			return 0;
			break;
		default:
			printf("�޴�ѡ�\n");
			break;
		}
	}

	while (1);
	return 0;
}
