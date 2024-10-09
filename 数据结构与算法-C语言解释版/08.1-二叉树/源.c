#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

//������
#define STATE_DATA 6666
//�Ƕ���ʾ������
#define IS_SHOW 1

/*������
	������������ӵ���
	���룺
		����->��һ���ڵ�������ж�Ϊ�վ͸�ֵ
		�ǿ���->�涨����������룬����һ�������ǣ����������ǾͲ��������Ҳ���
	������
		����ı�����
			����������� �� ��
			����������� �� ��
			����������� �� ��
			�����������壬�پֲ��������壬�پֲ�������
		��֪��������򣬿����Ƶ���������
		��֪����ͺ��򣬿����Ƶ���������
		��֪����ͺ��򣬲����Ƶ���������
	ɾ����
		1.ɾ���ڵ�
			���ڵ���Һ��ӳ�Ϊ�µĸ��ڵ㣬���ӳ�Ϊ �µĸ��ڵ� ��������
			��û���Һ��ӣ���ô���ڵ�����ӳ�Ϊ�µĸ��ڵ�
		2.�Ǹ��ڵ�
			�ҵ���ɾ�ڵ�����ĸ��ڵ�
			��ɾ�ڵ��������ڵ�����ӣ�
				��ɾ�ڵ�����ӳ�Ϊ���ҽڵ��������
				��ɾ�ڵ���Һ��ӳ�Ϊ�����ڵ�����ӣ������ɾ�ڵ��λ�ã�
			��ɾ�ڵ��������ڵ���Һ��ӣ�
				��ɾ�ڵ�����ӳ�Ϊ���ҽڵ��������
				��ɾ�ڵ���Һ��ӳ�Ϊ�����ڵ���Һ��ӣ������ɾ�ڵ��λ�ã�
*/
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
bool insertNode(struct Node** proot,int insertData) {
	if (proot == NULL)return false;
	if (*proot == NULL) {
		//����ǿ���
		*proot = createNode(insertData);
		return true;
	}
	//�ǿ���
	if (STATE_DATA == (*proot)->data)return false;
	//������������
	if(insertNode(&((*proot)->pLeft), insertData))return true;
	//������������
	insertNode(&((*proot)->pRight), insertData);
}

//�������
void preTravel(struct Node* proot) {
	if (NULL == proot)return;
	
	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

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

	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

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

	if (IS_SHOW == 0 && proot->data == STATE_DATA)return;

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
			return true;

		}

		
		
		
		
	}
	return false;
}

int main() {
	struct Node* root = NULL;
	int arr[] = { 8,63,STATE_DATA,STATE_DATA ,17,7,44,STATE_DATA ,38,STATE_DATA ,STATE_DATA ,STATE_DATA ,5,STATE_DATA };

	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		insertNode(&root,arr[i]);
	}

	travel(root, -1);
	travel(root, 0);
	travel(root, 1);

	int n;
	while (true)
	{
		printf("������Ҫɾ���Ľڵ㣺");
		scanf("%d", &n);
		deleteNode(&root, n);
		travel(root, 1);
	}

	while (1);
	return 0;
}
