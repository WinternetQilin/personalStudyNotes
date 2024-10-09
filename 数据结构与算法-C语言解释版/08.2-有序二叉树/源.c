#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//���Ľڵ�����
struct Node {
	int data;
	struct Node* pLeft;
	struct Node* pRight;
};

//�����ڵ�
struct Node* createNode(int data) {
	struct Node* pNew = malloc(sizeof(struct Node));
	if (NULL == pNew)return NULL;
	pNew->data = data;
	pNew->pLeft = pNew->pRight = NULL;
	return pNew;
}

//����ڵ�
bool insertNode(struct Node** proot, int insertData) {
	if (proot == NULL)return false;
	if (*proot == NULL) {
		//����ǿ���
		*proot = createNode(insertData);
		return true;
	}
	//������������
	if (insertData < (*proot)->data) {
		return insertNode(&((*proot)->pLeft), insertData);
	}
	//������������
	if (insertData > (*proot)->data) {
		return insertNode(&((*proot)->pRight), insertData);
	}
}

//�������
void preTravel(struct Node* proot) {
	if (NULL == proot)return;

	//�ȸ�
	printf("%4d ", proot->data);
	//����
	preTravel(proot->pLeft);
	//����
	preTravel(proot->pRight);
}
//�������
void midTravel(struct Node* proot) {
	if (NULL == proot)return;

	//����
	midTravel(proot->pLeft);
	//�ٸ�
	printf("%4d ", proot->data);
	//����
	midTravel(proot->pRight);
}
//�������
void lstTravel(struct Node* proot) {
	if (NULL == proot)return;

	//����
	lstTravel(proot->pLeft);
	//����
	lstTravel(proot->pRight);
	//���
	printf("%4d ", proot->data);
}

//����
void travel(struct Node* proot, int type) {
	if (type < 0) {
		//����
		printf("���������");
		preTravel(proot);
		printf("\n");
	}
	else if (0 == type) {
		//����
		printf("���������");
		midTravel(proot);
		printf("\n");
	}
	else {
		//����
		printf("���������");
		lstTravel(proot);
		printf("\n");
	}
}

//���ҽڵ�
struct Node* findNode(struct Node* proot,int findData){
	if (NULL == proot)return NULL;
	while (proot) {
		if (findData == proot->data)return proot;
		if (findData < proot->data) {
			proot = proot->pLeft;
		}
		else {
			proot = proot->pRight;
		}
	}

	return NULL;
}

//ɾ����Ӧ���ݵĽڵ㣨�������ظ���
bool deleteNode(struct Node** pproot, int delData) {
	if (NULL == pproot || NULL == *pproot)return false;
	struct Node* pDel = NULL;
	//1.ɾ���ڵ�
	if (delData == (*pproot)->data) {
		//��ʱ�洢���ڵ���Һ���
		//struct Node* pTempR = (*pproot)->pRight;
		//1.2���û���Һ��ӣ��Ǿ͸��ڵ�����ӳ�Ϊ�µĸ��ڵ�
		if (NULL == (*pproot)->pRight) {
			pDel = *pproot;
			*pproot = (*pproot)->pLeft;
			free(pDel);
			pDel = NULL;
			return true;
		}
		else {
			//1.1�Һ��ӳ�Ϊ�µĸ��ڵ�,���ӳ�Ϊ�µĸ��ڵ��������
			struct Node* pTempR = (*pproot)->pRight;
			while (pTempR->pLeft)
			{
				pTempR = pTempR->pLeft;
			}
			pTempR->pLeft = (*pproot)->pLeft;
			pDel = *pproot;
			*pproot = (*pproot)->pRight;
			free(pDel);
			pDel = NULL;
			return true;

		}
	}

	//2.ɾ���Ǹ��ڵ�
	pDel = findNode(*pproot, delData);
	if (NULL == pDel) return false;
	struct Node* pTemp = *pproot;
	struct Node* pDelParent = NULL;

	//��ɾ���ڵ�ĸ��ڵ�
	while (1) {
		pDel = pTemp;
		if (delData == pTemp->data)break;
		pDelParent = pTemp;
		if (delData < pTemp->data) {
			pTemp = pTemp->pLeft;
		}
		else {
			pTemp = pTemp->pRight;
		}
	}
	if (pDel == pDelParent->pLeft) {
		//Ҫɾ�ڵ����丸�ڵ������
		if (NULL == pDel->pRight) {
			//Ҫɾ�ڵ�û���Һ���,ֱ���������ӳ�Ϊ���ڵ������
			pDelParent->pLeft = pDel->pLeft;
			free(pDel);
			return true;
		}
		pTemp = pDel->pRight;
		while (pTemp->pLeft)
		{
			pTemp = pTemp->pLeft;
		}
		//1.pdel�����ӳ�Ϊpdel�Һ��ӵ�������
		pTemp->pLeft = pDel->pLeft;
		//2.pdel���Һ��ӳ�Ϊ���ڵ������
		pDelParent->pLeft = pDel->pRight;

		free(pDel);
		pDel = NULL;
		return true;
	}
	else {
		//Ҫɾ�ڵ����丸�ڵ�������
		//ͬ��
		if (NULL == pDel->pRight) {
			pDelParent->pRight = pDel->pLeft;
			free(pDel);
			return true;
		}
		pTemp = pDel->pRight;
		while (pTemp && pTemp->pLeft)
		{
			pTemp = pTemp->pLeft;
		}
		pTemp->pLeft = pDel->pLeft;
		pDelParent->pRight = pDel->pRight;
		free(pDel);
		pDel = NULL;
		return true;
	}

	return false;
}

int main() {
	struct Node* root = NULL;

	int arr[] = { 7,1,9,8,6,5,2,44,38,96,57,66,83 };

	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		insertNode(&root, arr[i]);
	}
	travel(root, 0);

	int n;
	while (true)
	{
		printf("������Ҫɾ���Ľڵ㣺");
		scanf("%d", &n);
		deleteNode(&root, n);
		travel(root, 0);
		printf("\n");
	}

	while (1);
	return 0;
}