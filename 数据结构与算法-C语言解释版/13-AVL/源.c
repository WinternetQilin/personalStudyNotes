#include<stdio.h>
#include<malloc.h>
#include<string.h>

/*
ƽ���������AVL����
������ڵ��������ڵ�����̫�����̫�٣�����Ч�ʾͲ���
	����Ҫ�������߽ڵ��������
	�������������߶Ȳ����1�����������
		�߶ȣ�������ڵ�Ľڵ�������·�����ȣ�����˵������
��ι�����
	1.�Ȱ�����������ķ�ʽ����
	2.��������Ƿ�ƽ��
		���ƽ�⣬���ù�
		��������ƽ�⣬ͨ����ת����ƽ��
��ƽ�������������Ǿֲ����������������ģ���
1.					o(���ڵ�)
				o(��ǰ�ڵ�)
			o(�½ڵ�)
�Ը��ڵ�Ϊ��������
					o18								o16
				o16				���			o7		o18
			o7

	1.��ʱ�洢���ڵ������pTemp
	2.��pTemp���Һ��ӳ�Ϊ���ڵ������
	3.���ڵ��ΪpTemp���Һ���
	4.�����¸߶�
	5.����pTemp��Ϊ�µ�pRoot


2.					o
						o
							o
�Ը��ڵ�Ϊ��������
					o1										o3
						o3				���			o1		o5
							o5



3.					o
				o
				   o

��������
���Ե�ǰ�ڵ�Ϊ�����������Ը��ڵ�Ϊ������
					o10							o10									o6
				o5				�ȱ��		o6					�ٱ��			o5		o10
					o6					o5
	
	1.

4.
					o
						o
					 o
��������
���Ե�ǰ�ڵ�Ϊ�����������Ը��ڵ�Ϊ������
					o10								o10									o12
						o18			�ȱ��				o12				�ٱ��		o10		o18
					 o12									o18

*/

//ƽ��������ڵ�����
struct treeNode {
	int data;
	struct treeNode* pL;
	struct treeNode* pR;
	int height;//ע��߶�
};

//�����ڵ㺯��
struct treeNode* createNode(int data) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew) {
		printf("�����ڵ�ʧ�ܣ�");
		return NULL;
	}

	pNew->data = data;
	pNew->pL = NULL;
	pNew->pR = NULL;
	pNew->height = 0;

	return pNew;
}

//��ȡĳ���ڵ�ĸ߶�
int getHeight(struct treeNode* pRoot) {
	if (NULL == pRoot)return 0;
	return pRoot->height;
}

//���1-����
struct treeNode* RR(struct treeNode* pRoot) {
	struct treeNode* pTemp = pRoot->pL;
	pRoot->pL = pTemp->pR;
	pTemp->pR = pRoot;

	//���ø߶�
	int LHeight = getHeight(pRoot->pL);
	int RHeight = getHeight(pRoot->pR);
	pRoot->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	LHeight = getHeight(pTemp->pL);
	RHeight = getHeight(pTemp->pR);
	pTemp->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	return pTemp;

}
//���2-����
struct treeNode* LL(struct treeNode* pRoot) {
	struct treeNode* pTemp = pRoot->pR;
	pRoot->pR = pTemp->pL;
	pTemp->pL = pRoot;

	//���ø߶�
	int LHeight = getHeight(pRoot->pL);
	int RHeight = getHeight(pRoot->pR);
	pRoot->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	LHeight = getHeight(pTemp->pL);
	RHeight = getHeight(pTemp->pR);
	pTemp->height = 1 + (LHeight > RHeight ? LHeight : RHeight);

	return pTemp;
}

//���3-������
struct treeNode* LR(struct treeNode* pRoot) {
	//����pRoot������Ϊ������
	pRoot->pL = LL(pRoot->pL);
	//����pRootΪ������
	return RR(pRoot);
}
//���4-������
struct treeNode* RL(struct treeNode* pRoot) {
	//����pRoot���Һ���Ϊ������
	pRoot->pR = RR(pRoot->pR);
	//����pRootΪ������
	return LL(pRoot);
}

//����ڵ�
void insertNode(struct treeNode** pRoot, int inData) {
	if (NULL == pRoot)return;
	//�ʼ��������������ķ�ʽ����
	if (NULL == *pRoot) {
		*pRoot = createNode(inData);
	}
	else if (inData < (*pRoot)->data) {
		//�������
		insertNode(&((*pRoot)->pL), inData);
		//������ɺ���߶ȣ�ע�⣬������룬ֻ����߸߶ȴ����ұߵĿ���û���ұߴ�����ߵĿ��ܣ�
		if (getHeight((*pRoot)->pL) - getHeight((*pRoot)->pR) > 1) {
			//��ƽ�� ���1�������3
			if (inData < (*pRoot)->pL->data) {
				//���1-����
				*pRoot = RR((*pRoot));
			}
			else {
				//���3-������
				*pRoot = LR((*pRoot));
			}
		}
	}
	else {
		//���Ҳ���
		insertNode(&((*pRoot)->pR), inData);
		if (getHeight((*pRoot)->pR) - getHeight((*pRoot)->pL) > 1) {
			//��ƽ�� ���2�������4
			if (inData < (*pRoot)->pR->data) {
				//���4-������
				*pRoot = RL((*pRoot));
			}
			else {
				//���2-����
				*pRoot = LL((*pRoot));
			}
		}
	}

	//���ø߶�
	int LHeight = getHeight((*pRoot)->pL);
	int RHeight = getHeight((*pRoot)->pR);
	(*pRoot)->height = 1 + (LHeight > RHeight ? LHeight : RHeight);
}

//�������
void preTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//�ȸ�
	printf("%4d ", proot->data);
	//����
	preTravel(proot->pL);
	//����
	preTravel(proot->pR);
}
//�������
void midTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//����
	midTravel(proot->pL);
	//�ٸ�
	printf("%4d(%d) ", proot->data,proot->height);
	//����
	midTravel(proot->pR);
}
//�������
void lstTravel(struct treeNode* proot) {
	if (NULL == proot)return;

	//����
	lstTravel(proot->pL);
	//����
	lstTravel(proot->pR);
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
		printf("�������(������Ϊ�߶�)��");
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

int main() {
	int arr[] = {38,66,56,39,41,58,18,8,99,78,33,76,36,45,92,3};
	int len = 16;

	struct treeNode* root = NULL;

	for (int i = 0; i < len; i++)
	{
		insertNode(&root, arr[i]);
		travel(root, 0);
	}

	while (1);
	return 0;
}
