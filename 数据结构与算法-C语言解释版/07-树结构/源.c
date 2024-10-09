#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#define NUM 11

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

/*�鲢����
	����������������ϲ���һ����������
	���������ù鲢����ȥ�ţ�����ϰʹ�ã�һ�㲻Ҫ�ù鲢���������飬Ч��̫�ͣ���
*/

//������������ϲ���һ����������
void MergeSort(int arr[NUM], int l, int m, int r) {
	int left = l;
	int right = m + 1;
	int len = r - l + 1;
	int* pTemp = (int*)malloc(sizeof(int) * len);
	int k = 0;
	while (left <= m && right <= r) {
		if (arr[left] < arr[right]) {
			pTemp[k++] = arr[left++];
		}
		else {
			pTemp[k++] = arr[right++];
		}
	}
	//��ĳһ��ʣ�µķ���
	while (left <= m) {
		pTemp[k++] = arr[left++];
	}
	while (right <= r) {
		pTemp[k++] = arr[right++];
	}
	//����ʱ�ڴ渲������
	k = 0;
	for (int i = l; i < r; i++) {
		arr[i] = pTemp[k++];
	}
	//�ͷ���ʱ�ڴ�
	free(pTemp);
}

void mergeSort(int arr[NUM], int left, int right) {
	if (left < right) {
		//��
		int m = left + (right - left) / 2;
		mergeSort(arr, left, m);//���
		mergeSort(arr, m + 1, right);//�ұ�
		//�ϲ�
		MergeSort(arr, left, m, right);
		printf("left:%d  m:%d  right:%d\n", left, m, right);
		travel(arr+left, right - left + 1, false);
	}
}

void merge_sort(int arr[NUM], int len) {
	mergeSort(arr, 0, len - 1);
}

/*���ṹ
	��ʵ����ľ�Ǵ������ϳ��������Ǹ���������֦�ɣ�����������֦����Ҷ
	����Ա�������������»�
		����������		���ڵ�
		�м���֦��		֦�ɽڵ�
		��������Ҷ		Ҷ�ӽڵ�

		���ṹ��Ȼ�߱��ݹ�����
		���еĽڵ㣬Ҳ���Կ���������һ���� - ����
		�棺
			һ����		����������
			������		������
			������		������
			�Դ�����...
			��ĳһ�ڵ�ֲ����Ķ���Ϊ��������
				�������ĸ��ڵ����������һ�������������ӽڵ㣬��ô����Ϊ������
*/
/*����ָ������һ����
	���룺
		�����Ϊĳ���ڵ�ĺ��ӻ����ֵ�
			��Ϊ���ӣ�
				1.�޺��ӣ���Ϊ����
				2.�к��ӣ���Ϊ��С�ĺ���
			��Ϊ�ֵ�:
				1.���ֵܣ���Ϊ�ֵ�
				2.���ֵܣ���Ϊ��С���ֵ�
*/

struct treeNode
{
	//������
	int data;
	//ָ����
	struct treeNode* pParent;//���ڵ�
	struct treeNode* pBrother;//�ֵܽڵ�
	struct treeNode* pChild;//�ӽڵ�
};

//�����ڵ㺯��
struct treeNode* createNode(int data) {
	struct treeNode* pNew = malloc(sizeof(struct treeNode));
	memset(pNew, 0, sizeof(struct treeNode));
	pNew->data = data;
	return pNew;
}

//���ҽڵ㺯��(�ҵ�����Ŀ��ڵ��ָ�룬û�ҵ�����NULL)
struct treeNode* findNode(struct treeNode* ptree,int findData) {
	if (NULL == ptree)return NULL;
	//�ȿ��Ƿ�Ϊ��ǰ�ڵ�
	struct treeNode* pCurrent = ptree;
	
	//Ȼ��ѭ���Һ���
	while (pCurrent) {
		//ѭ�����ֵ�
		struct treeNode* pBrother = pCurrent;
		while (pBrother) {
			//ѭ�����ֵܵĺ���
			struct treeNode* pChild = pBrother;
			while (pChild)
			{
				if (findData == pChild->data) {
					return pChild;
				}
				//��һ������
				pChild = pChild->pChild;
			}
			
			//��һ���ֵ�
			pBrother = pBrother->pBrother;
		}
		//��һ���ֵ�
		pCurrent = pCurrent->pChild;
	}
	//ѭ��������û�У��Ǿ�û����
	return NULL;
}

//����ڵ㺯��
//������Ҫ�Ķ��������Դ����Ķ���ָ�룬��boolֵ���Ʋ���Ϊ�ӽڵ㻹���ֵܽڵ�
void insertNode(struct treeNode** ptree,int findData, int insertData, bool isChild) {
	if (NULL == ptree)return;
	struct treeNode* pNew = createNode(insertData);
	if (NULL==*ptree) {
		//����
		*ptree = pNew;
		return;
	}
	struct treeNode* found = findNode(*ptree, findData);
	//û�ҵ�
	if (NULL == found) {
		printf("û�ҵ���Ӧ�ڵ�\n");
		return NULL;
	}
	//�ҵ���
	if (isChild) {
		//��Ϊ����
		if (found->pChild) {
			//�к���
			while (found->pChild)
			{
				found = found->pChild;
			}
			found->pChild = pNew;
			pNew->pParent = found;
		}
		else {
			//û�к���
			found->pChild = pNew;
			pNew->pParent = found;
		}
	}
	else {
		//��Ϊ�ֵ�
		if (found->pBrother) {
			//���ֵ�
			while (found->pBrother) {
				found = found->pBrother;
			}
			found->pBrother = pNew;
			pNew->pParent = found->pParent;
		}
		else {
			//���ֵ�
			found->pBrother = pNew;
			pNew->pParent = found->pParent;
			return;
		}
	}
}

int main() {
	/*
	int arr[NUM] = { 12,39,48,53,66,1,9,41,72,99,666 };
	travel(arr, NUM, false);

	printf("�鲢����\n");
	merge_sort(arr, NUM);

	travel(arr, NUM, true);
	*/
	//��	���ĸ��ڵ�
	struct treeNode* pRoot = NULL;

	insertNode(&pRoot, 10, 1, true);
	insertNode(&pRoot, 1, 2, true);
	insertNode(&pRoot, 1, 3, true);
	insertNode(&pRoot, 2, 22, false);
	insertNode(&pRoot, 2, 24, false);
	insertNode(&pRoot, 24, 333, true);
	insertNode(&pRoot, 24, 444, true);


	while (1);
	return 0;
}
