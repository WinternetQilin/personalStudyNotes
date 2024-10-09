#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

/*
* 23����
�����ƽ�������������ɾ��Ч�ʸ���
���ڵ㣺һ�����ݣ�����ָ��
���ڵ㣺�������ݣ�����ָ��
�Ľڵ㣨��ʱ���ڣ����������ݣ��ĸ�ָ��
*/

enum types {
	null_node,
	two_node,
	three_node,
	four_node
};

//�ڵ�����
struct treeNode {
	//�����2�ڵ㣨1������3�ڵ㣨2������4�ڵ㣨3��
	int cnt;
	//����
	int data[3];
	//ָ��
	struct treeNode* pArr[4];
};

//�����ڵ㺯��
struct treeNode* createNode() {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	if (NULL == pNew)return NULL;
	memset(pNew, 0, sizeof(struct treeNode));
	return pNew;
}

//����ڵ㵽����
void insertNode(struct treeNode** pRoot, int inData) {
	if (NULL == pRoot)return;
	if (NULL == *pRoot) {
		//����
		*pRoot = createNode();
		(*pRoot)->cnt = two_node;
		(*pRoot)->data[0] = inData;
	}
	else {
		//������ǿ���
		inNode(*pRoot, NULL, inData);
	}
}
//ʵ�ʵĲ��뺯��
void inNode(struct treeNode* node, struct treeNode* parent, int inData) {
	if (NULL == node)return;
	if (null_node == node->cnt) {
		node->data[0] = inData;
		node->cnt++;
		return;
	}
	if (two_node == node->cnt) {
		if (inData > node->data[0]) {//���ұ߷�
			//�ж���û�к��ӣ��к��ӵĻ���Ҫ�嵽������
			if (node->pArr[1]) {//�к���
				inNode(node->pArr[1], node, inData);
			}
			else {
				node->data[1] = inData;
				node->cnt++;//������ڵ�
			}
			
		}
		else {//����߷�
			//�ж���û�к��ӣ��к��ӵĻ���Ҫ�嵽������
			if (node->pArr[0]) {//�к���
				inNode(node->pArr[0], node, inData);
			}
			else {
				//�Ƚ�����������Ų��
				node->data[1] = node->data[0];
				//�ٽ��½ڵ�ŵ���һ��
				node->data[0] = inData;
				node->cnt++;
			}
		}
	}
	if (three_node == node->cnt) {
		if (inData<node->data[0]) {//�������
			if (node->pArr[0]) {//�к���
				inNode(node->pArr[0], node, inData);
			}
			else {//û�к���
				//��ǰ����������Ų��
				node->data[2] = node->data[1];
				node->data[1] = node->data[0];
				//�����ݽ���
				node->data[0] = inData;
				//����Ľڵ�
				node->cnt++;
			}
		}
		else if (inData<node->data[1]) {//���м����
			if (node->pArr[1]) {//�к���
				inNode(node->pArr[1], node, inData);
			}
			else {//û�к���
				node->data[2] = node->data[1];
				//�����ݽ���
				node->data[1] = inData;
				//����Ľڵ�
				node->cnt++;
			}
		}
		else {//���Ҳ���
			if (node->pArr[2]) {//�к���
				inNode(node->pArr[2], node, inData);
			}
			else {//û�к���
				node->data[2] = inData;
				//����Ľڵ�
				node->cnt++;
			}
		}
	}
	//�ж�һ���Ƿ�������Ľڵ�
	if (four_node == node->cnt) {
		//���������½ڵ�
		struct treeNode* nodeL = createNode();
		struct treeNode* nodeR = createNode();
		//�½ڵ㸳ֵ
		//��
		nodeL->cnt = two_node;
		nodeL->data[0] = node->data[0];
		nodeL->pArr[0] = node->pArr[0];
		nodeL->pArr[1] = node->pArr[1];
		//��
		nodeR->cnt = two_node;
		nodeR->data[0] = node->data[2];
		nodeR->pArr[0] = node->pArr[2];
		nodeR->pArr[1] = node->pArr[3];

		//��ʱ�洢�м�ֵ
		int temp = node->data[1];
		//���и��ڵ㣬�Ը��ڵ�������
		if (parent) {
			//
			if (temp < parent->data[0]) {//����������
				if (parent->pArr[2]) {//���ұ��к���
					parent->data[2] = parent->data[1];
					parent->data[1] = parent->data[0];
					parent->data[0] = temp;

					parent->pArr[3] = parent->pArr[2];
					parent->pArr[2] = parent->pArr[1];
					parent->pArr[1] = nodeR;
					parent->pArr[0] = nodeL;

				}
				else if (parent->pArr[1]) {//�м��к���
					parent->data[1] = parent->data[0];
					parent->data[0] = temp;

					parent->pArr[2] = parent->pArr[1];
					parent->pArr[1] = nodeR;
					parent->pArr[0] = nodeL;
				}
			}
			else if ((two_node == parent->cnt) ||(parent->cnt>1)&& temp < parent->data[1]) {//���м����

				if (parent->pArr[2]) {//���ұ��к���
					parent->data[2] = parent->data[1];
					parent->data[1] = temp;

					parent->pArr[3] = parent->pArr[2];
					parent->pArr[2] = nodeR;
					parent->pArr[1] = nodeL;

				}
				else if (parent->pArr[1]) {//�м��к���
					parent->data[1] = temp;

					parent->pArr[2] = nodeR;
					parent->pArr[1] = nodeL;
				}

			}
			else if ((three_node == parent->cnt) || (parent->cnt > 2) && temp < parent->data[2]) {//���ұ߲���
				parent->data[2] = temp;

				parent->pArr[3] = nodeR;
				parent->pArr[2] = nodeL;
			}

			//���ڵ�仯
			parent->cnt++;
			//��ǰ�ڵ��ͷ�
			free(node);

		}
		else {//��û�и��ڵ㣬��ǰ�ڵ�仯

			//����սڵ�
			memset(node->data, 0, sizeof(int) * 3);
			memset(node->pArr, 0, sizeof(struct treeNode) * 4);

			//��ǰ�ڵ��ɶ��ڵ�
			node->cnt = two_node;
			//���ݱ仯
			node->data[0] = temp;
			//ָ��仯
			node->pArr[0] = nodeL;
			node->pArr[1] = nodeR;

		}
		
	}
}

int main() {

	int arr[] = { 38,66,56,39,41,58,18,8,99,78,33,76,36,45,92,3 };
	int len = 16;

	struct treeNode* root = NULL;

	for (int i = 0; i < len; i++)
	{
		insertNode(&root, arr[i]);
	}

	return 0;
}
