#include<iostream>

using namespace std;

struct Node {
	int data;
	struct Node* LChild;
	struct Node* RChild;
};

//�����ڵ�
struct Node* createNode(int insertData) {
	struct Node* pNew = (struct Node*)malloc(sizeof(struct Node));

	while (nullptr == pNew)
	{
		pNew = (struct Node*)malloc(sizeof(struct Node));
	}

	pNew->data = insertData;
	pNew->LChild = nullptr;
	pNew->RChild = nullptr;
	return pNew;
}

//����ڵ㣨��������������ķ�ʽ���룩
void insertNode(struct Node*& root, int insertData) {
	if (nullptr == root) {
		root = createNode(insertData);
		return;
	}
	else if (insertData < root->data) {
		insertNode(root->LChild, insertData);
		return;
	}
	else if (insertData > root->data) {
		insertNode(root->RChild, insertData);
		return;
	}
}

//�������
void preorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//��
	cout << root->data << " ";
	//��
	preorder(root->LChild);
	//��
	preorder(root->RChild);
}

//�������
void inorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//��
	inorder(root->LChild);
	//��
	cout << root->data << " ";
	//��
	inorder(root->RChild);
}

//�������
void postorder(struct Node* root) {
	if (nullptr == root) {
		return;
	}
	//��
	postorder(root->LChild);
	//��
	postorder(root->RChild);
	//��
	cout << root->data << " ";
}

//ɾ�����������ظ��ģ�
void deleteNode(struct Node*& root, int delData) {
	if (nullptr == root)return;

	//��ɾ�ڵ��Ǹ��ڵ�
	if (delData == root->data) {
		//���û���Һ��ӣ����ӳ�Ϊ�µĸ��ڵ�
		if (nullptr == root->RChild) {
			struct Node* pDel = root;
			root = root->LChild;
			free(pDel);
			pDel = nullptr;
			return;
		}
		else {
			//�����Һ��ӣ��Һ��ӳ�Ϊ�µĸ��ڵ㣬���ӳ�Ϊ�µĸ��ڵ��������

			//��������ӵĻ�
			if (nullptr != root->LChild) {
				struct Node* pTemp = root->RChild;
				while (pTemp->LChild)
				{
					pTemp = pTemp->LChild;
				}
				//���ӳ�Ϊ�µĸ��ڵ��������
				pTemp->LChild = root->LChild;
			}

			//�Һ��ӳ�Ϊ�µĸ��ڵ�
			struct Node* pDel = root;
			root = root->RChild;
			free(pDel);
			pDel = nullptr;
			return;
		}
	}

	//ɾ���Ǹ��ڵ�
	if (delData < root->data) {
		deleteNode(root->LChild, delData);
	}
	else {
		deleteNode(root->RChild, delData);
	}
}

//���ҽڵ�
struct Node* findNode(struct Node* root, int destData) {
	if (nullptr == root)return nullptr;
	while (root) {
		if (destData == root->data)return root;
		if (destData < root->data) {
			root = root->LChild;
		}
		else {
			root = root->RChild;
		}
	}

	return nullptr;
}

//�޸Ľڵ�
void modifyNode(struct Node*& root, int oldData,int newData) {
	if (nullptr == root)return;
	deleteNode(root, oldData);
	insertNode(root, newData);
}

int main() {
	//����һ����
	struct Node* tree = nullptr;
	//׼��Ҫ���������
	int arr[] = { 7,1,9,8,6,5,2,44,38,96,57,66,83 };
	//��������
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		insertNode(tree, arr[i]);
	}

	/*cout << "���������";
	preorder(tree);
	cout << endl;

	cout << "���������";
	inorder(tree);
	cout << endl;

	cout << "���������";
	postorder(tree);
	cout << endl;*/

	cout << "���������";
	preorder(tree);
	cout << endl;
	int n;
	while (true)
	{
		cout << "������Ҫɾ�������ݣ�";
		cin >> n;
		deleteNode(tree, n);
		cout << "���������";
		preorder(tree);
		cout << endl;
	}

	return 0;
}
